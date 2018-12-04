#include "GameState.h"
#include "graphics\sprite_renderer.h"
#include "graphics\renderer_3d.h"
#include "input\input_manager.h"
#include "input\sony_controller_input_manager.h"
#include "graphics\font.h"
#include <maths/math_utils.h>
#include <algorithm>
#include "system/platform.h"
#include "input/keyboard.h"
#include <graphics\sprite.h>

// Vita AR includes
#include <camera.h>
#include <gxm.h>
#include <motion.h>
#include <libdbg.h>
#include <libsmart.h>

#include <sony_sample_framework.h>
#include <sony_tracking.h>

GameState::GameState() : 
	BaseState()
{
}


GameState::~GameState()
{
}

void GameState::Init(gef::Platform & platform)
{
	inputManager = gef::InputManager::Create(platform);

	m_world = new World(platform);
	InitCamera(platform);
}

void GameState::Cleanup()
{
	smartRelease();
	sampleRelease();
}

void GameState::CleanUpFont(gef::Font* font)
{
	delete font;
	font = NULL;
}

void GameState::InitCamera(gef::Platform &platform)
{
	// initialise sony framework
	sampleInitialize();
	smartInitialize();

	// reset marker tracking
	AppData* dat = sampleUpdateBegin();
	smartTrackingReset();
	sampleUpdateEnd(dat);

	float cameraAspect = (float)SCE_SMART_IMAGE_WIDTH / (float)SCE_SMART_IMAGE_HEIGHT;
	float displayAspect = (float)platform.width() / (float)platform.height();

	m_vScale = displayAspect / cameraAspect;

	m_cameraSprite = new gef::Sprite();
	m_cameraSprite->set_position(0.0f, 0.0f, 1.0f);
	m_cameraSprite->set_width(2.0f);
	m_cameraSprite->set_height(2.0f * m_vScale);
	m_cameraSprite->set_texture(&m_cameraTexture);
}

void GameState::DrawHUD(gef::Font* font, gef::SpriteRenderer* spriteRenderer)
{
	if (font)
	{
		// display frame rate
		font->RenderText(spriteRenderer, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

void GameState::SetupLights(gef::Renderer3D* renderer3D)
{
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));

	gef::Default3DShaderData& default_shader_data = renderer3D->default_shader_data();
	default_shader_data.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void GameState::SetupGameCamera()
{
	// initialise the camera settings
	camera_eye_ = gef::Vector4(-500.0f, 5.0f, 5.0f);
	camera_lookat_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_fov_ = gef::DegToRad(45.0f);
}

int GameState::Update(gef::Platform & platform, float deltaTime)
{
	fps_ = 1.0f / deltaTime;

	//Read camera data and attempt to find scene markers
	AppData* dat = sampleUpdateBegin();
	smartUpdate(dat->currentImage);

	if (sampleIsMarkerFound(0))
	{
		gef::Matrix44 markerTransform;
		sampleGetTransform(0, &markerTransform);

		gef::Matrix44 playerTransform = m_world->Player()->transform();
		playerTransform.Scale(gef::Vector4(0.002f, 0.002f, 0.002f));
		playerTransform.SetTranslation(markerTransform.GetTranslation());

		
		m_world->Player()->set_transform(playerTransform);
		
	}

	sampleUpdateEnd(dat);



	// read input devices
	if (inputManager)
	{
		inputManager->Update();

		//Controller input
		gef::SonyControllerInputManager* controller_manager = inputManager->controller_input();
		if (controller_manager)
		{
			float x = controller_manager->GetController(0)->left_stick_x_axis();
			float y = controller_manager->GetController(0)->left_stick_y_axis();

			m_world->Player()->Move(gef::Vector4(0.0f, 1.0f * y, 1.0f * x), m_world, deltaTime);
		}


		// keyboard input
		gef::Keyboard* keyboard = inputManager->keyboard();
		if (keyboard)
		{
			if (keyboard->IsKeyDown(gef::Keyboard::KC_RIGHT))
				m_world->Player()->Move(gef::Vector4(0.0f, 0.0f, 1.0f), m_world, deltaTime);

			if (keyboard->IsKeyDown(gef::Keyboard::KC_LEFT))
				m_world->Player()->Move(gef::Vector4(0.0f, 0.0f, -1.0f), m_world, deltaTime);

			if (keyboard->IsKeyDown(gef::Keyboard::KC_UP))
				m_world->Player()->Move(gef::Vector4(0.0f, 1.0f, 0.0f), m_world, deltaTime);

			if (keyboard->IsKeyDown(gef::Keyboard::KC_DOWN))
				m_world->Player()->Move(gef::Vector4(0.0f, -1.0f, 0.0f), m_world, deltaTime);
		
		}
	}

	return 0;
}

void GameState::Render(gef::Platform &platform, gef::SpriteRenderer * spriteRenderer, gef::Renderer3D * renderer3D)
{
	AppData* dat = sampleRenderBegin();

	if (dat->currentImage)
	{
		m_cameraTexture.set_texture(dat->currentImage->tex_yuv);
		m_cameraSprite->set_texture(&m_cameraTexture);
	}

	//Matrix fun zone
	m_cameraOrthoMatrix.SetIdentity();
	m_cameraOrthoMatrix.OrthographicFrustumGL(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	spriteRenderer->set_projection_matrix(m_cameraOrthoMatrix);

	m_cameraOrientedOrthoMatrix = m_cameraOrthoMatrix;

	m_FOVProjectionMatrix = platform.PerspectiveProjectionFov((float)SCE_SMART_IMAGE_FOV, (float)SCE_SMART_IMAGE_WIDTH / (float)SCE_SMART_IMAGE_HEIGHT, near_plane_, far_plane_);
	m_scaleMatrix.SetIdentity();
	m_scaleMatrix.Scale(gef::Vector4(1.0f, m_vScale, 1.0f));
	m_finalProjectionMatrix = m_FOVProjectionMatrix * m_scaleMatrix;
	
	RenderOverlay(platform, spriteRenderer);

	renderer3D->set_projection_matrix(m_finalProjectionMatrix);
	renderer3D->set_view_matrix(m_cameraOrientedOrthoMatrix);

	renderer3D->Begin(false);

	for (int i = 0; i < m_world->WorldObjects().size(); i++)
		renderer3D->DrawMesh(*m_world->WorldObjects().at(i));

	renderer3D->End();
}

void GameState::RenderOverlay(gef::Platform &platform, gef::SpriteRenderer * renderer)
{
	renderer->Begin(true);
	renderer->DrawSprite(*m_cameraSprite);
	//DrawHUD(font, renderer);
	renderer->End();
}