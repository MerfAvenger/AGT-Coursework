#ifndef _RENDER_TARGET_APP_H
#define _RENDER_TARGET_APP_H

#include <system/application.h>
#include <graphics/sprite.h>
#include <maths/vector2.h>
#include <vector>
#include <graphics/mesh_instance.h>
#include <platform/vita/graphics/texture_vita.h>
#include "primitive_builder.h"

#include "StateManager.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class RenderTarget;
	class TextureVita;
	class InputManager;
}
class GameState;

class ARApp : public gef::Application
{
public:
	ARApp(gef::Platform& platform);
	void Init();
	void InitRendering();
	void InitFont();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:

	void RenderOverlay();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();

	gef::InputManager* m_inputManager;
	gef::SpriteRenderer* m_spriteRenderer;
	gef::Font* m_font;

	class gef::Renderer3D* m_renderer3D;

	float fps_;

	StateManager* m_stateManager;
};
#endif // _RENDER_TARGET_APP_H