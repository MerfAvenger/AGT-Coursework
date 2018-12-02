#include "starter_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>
#include <graphics/primitive.h>
#include <assets/png_loader.h>
#include <graphics/image_data.h>
#include <graphics/font.h>
#include <maths/vector2.h>
#include <input/input_manager.h>
#include <input/sony_controller_input_manager.h>
#include <input/keyboard.h>
#include <maths/math_utils.h>
#include <graphics/renderer_3d.h>
#include <graphics/scene.h>
#include <animation/skeleton.h>
#include <animation/animation.h>


StarterApp::StarterApp(gef::Platform& platform) :
	Application(platform),
	m_spriteRenderer(NULL),
	m_stateManager(NULL),
	m_font(NULL)
{
}

void StarterApp::Init()
{
	InitRendering();

	m_stateManager = new StateManager(platform_);
	m_stateManager->StateUpdate(platform_, m_spriteRenderer, m_renderer3D);
}

void StarterApp::InitRendering()
{
	m_spriteRenderer = gef::SpriteRenderer::Create(platform_);
	m_renderer3D = gef::Renderer3D::Create(platform_);
	
	InitFont();
}

void StarterApp::InitFont()
{
	m_font = new gef::Font(platform_);
	m_font->Load("comic_sans");
}

void StarterApp::CleanUp()
{

}

bool StarterApp::Update(float frame_time)
{
	int rVal = m_stateManager->Update(platform_, frame_time);

	if (rVal != 0)
	{
		m_stateManager->SetState(APPLICATION_STATE(rVal));
		m_stateManager->StateUpdate(platform_, m_spriteRenderer, m_renderer3D);
	}

	return true;
}

void StarterApp::Render()
{
	m_stateManager->Render(platform_, m_spriteRenderer, m_renderer3D);
}

