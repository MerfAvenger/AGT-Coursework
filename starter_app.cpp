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
	Application(platform)
{
}

void StarterApp::Init()
{
	m_stateManager = new StateManager(platform_);
}

void StarterApp::CleanUp()
{

}

bool StarterApp::Update(float frame_time)
{
	m_stateManager->Update(platform_, frame_time);
}

void StarterApp::Render()
{
	m_stateManager->Render(platform_);
}

