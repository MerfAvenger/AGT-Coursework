#include "ar_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/font.h>
#include <input/touch_input_manager.h>
#include <maths/vector2.h>
#include <input/input_manager.h>
#include <maths/math_utils.h>
#include <graphics/renderer_3d.h>
#include <graphics/render_target.h>
#include "GameState.h"


ARApp::ARApp(gef::Platform& platform) :
	Application(platform),
	m_inputManager(NULL),
	m_spriteRenderer(NULL),
	m_font(NULL),
	m_renderer3D(NULL)
{
}

void ARApp::Init()
{
	InitRendering();

	m_stateManager = new StateManager(platform_);
	m_stateManager->StateUpdate(platform_, m_spriteRenderer, m_renderer3D);

	SetupLights();
}

void ARApp::InitRendering()
{
	m_spriteRenderer = gef::SpriteRenderer::Create(platform_);
	m_renderer3D = gef::Renderer3D::Create(platform_);

	InitFont();
}

void ARApp::InitFont()
{
	m_font = new gef::Font(platform_);
	m_font->Load("comic_sans");
}


void ARApp::CleanUp()
{
	CleanUpFont();

	delete m_spriteRenderer;
	m_spriteRenderer = NULL;

	delete m_renderer3D;
	m_renderer3D = NULL;

	delete m_inputManager;
	m_inputManager = NULL;
}

bool ARApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	int rVal = m_stateManager->Update(platform_, frame_time);

	if (rVal != 0)
	{
		m_stateManager->SetState(APPLICATION_STATE(rVal));
		m_stateManager->StateUpdate(platform_, m_spriteRenderer, m_renderer3D);
	}

	return true;
}

void ARApp::Render()
{
	m_stateManager->Render(platform_, m_spriteRenderer, m_renderer3D);

	/*if (m_stateManager->StateInfo() == game)
		static_cast<GameState*>(m_stateManager->State())->DrawHUD();*/
}


void ARApp::RenderOverlay()
{
}

void ARApp::CleanUpFont()
{
	delete m_font;
	m_font = NULL;
}

void ARApp::DrawHUD()
{
	if(m_font)
	{
		m_font->RenderText(m_spriteRenderer, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);
	}
}

void ARApp::SetupLights()
{
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-300.0f, -500.0f, 100.0f));

	gef::Default3DShaderData& default_shader_data = m_renderer3D->default_shader_data();
	default_shader_data.set_ambient_light_colour(gef::Colour(0.5f, 0.5f, 0.5f, 1.0f));
	default_shader_data.AddPointLight(default_point_light);
}
