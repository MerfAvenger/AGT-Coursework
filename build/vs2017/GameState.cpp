#include "GameState.h"
#include "graphics\sprite_renderer.h"
#include "graphics\renderer_3d.h"
#include "input\input_manager.h"
#include "graphics\font.h"
#include <maths/math_utils.h>
#include <algorithm>
#include "system/platform.h"
#include "input/keyboard.h"

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
	SetupCamera();
}

void GameState::CleanUpFont(gef::Font* font)
{
	delete font;
	font = NULL;
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

void GameState::SetupCamera()
{
	// initialise the camera settings
	camera_eye_ = gef::Vector4(-500.0f, 5.0f, 5.0f);
	camera_lookat_ = gef::Vector4(0.0f, 0.0f, 0.0f);
	camera_up_ = gef::Vector4(0.0f, 1.0f, 0.0f);
	camera_fov_ = gef::DegToRad(45.0f);
	near_plane_ = 0.01f;
	far_plane_ = 100.f;
}

int GameState::Update(gef::Platform & platform, float deltaTime)
{
	fps_ = 1.0f / deltaTime;

	// read input devices
	if (inputManager)
	{
		inputManager->Update();

		// controller input
		gef::SonyControllerInputManager* controller_manager = inputManager->controller_input();
		if (controller_manager)
		{
		}

		// keyboard input
		gef::Keyboard* keyboard = inputManager->keyboard();
		if (keyboard)
		{
			if (keyboard->IsKeyDown(gef::Keyboard::KC_SPACE))
				m_world->Player()->Move(gef::Vector4(0.0f, 1.0f, 1.0f), m_world, deltaTime);
		}
	}

	return 0;
}

void GameState::Render(gef::Platform &platform, gef::SpriteRenderer * spriteRenderer, gef::Renderer3D * renderer3D)
{
	gef::Matrix44 projection_matrix;
	gef::Matrix44 view_matrix;

	projection_matrix = platform.PerspectiveProjectionFov(camera_fov_, (float)platform.width() / (float)platform.height(), near_plane_, far_plane_);
	view_matrix.LookAt(camera_eye_, camera_lookat_, camera_up_);
	renderer3D->set_projection_matrix(projection_matrix);
	renderer3D->set_view_matrix(view_matrix);

	renderer3D->Begin(true);

	for (int i = 0; i < m_world->WorldObjects().size(); i++)
		renderer3D->DrawMesh(*m_world->WorldObjects().at(i));

	renderer3D->End();

}
