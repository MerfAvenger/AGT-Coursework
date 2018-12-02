#ifndef _STARTER_APP_H
#define _STARTER_APP_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector2.h>
#include <maths/vector4.h>
#include <maths/matrix44.h>
#include <vector>
#include "World.h"
#include "primitive_builder.h"
#include <list>
#include "StateManager.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class Scene;
	class Skeleton;
	class InputManager;
}

class StarterApp : public gef::Application
{
public:
	StarterApp(gef::Platform& platform);
	void Init();
	void InitRendering();
	void InitFont();
	void CleanUp();
	bool Update(float frame_time);
	void Render();

private:

	gef::Renderer3D* m_renderer3D;
	gef::Font* m_font;
	gef::SpriteRenderer* m_spriteRenderer;

	StateManager* m_stateManager;
};

#endif // _STARTER_APP_H
