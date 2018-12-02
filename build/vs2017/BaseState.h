#ifndef BASESTATE_H
#define BASESTATE_H
#include "maths/vector4.h"

enum APPLICATION_STATE
{
	def,
	splash,
	menu,
	game,
	pause
};

namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class PNGLoader;
	class InputManager;
	class Renderer3D;
}

class BaseState
{

protected:
	
	
	virtual void Cleanup();
	
	gef::InputManager* inputManager;
	gef::PNGLoader* m_imageLoader;


public:
	BaseState();
	~BaseState();

	virtual void Init(gef::Platform &platform) = 0;
	virtual int Update(gef::Platform &platform, float deltaTime);
	virtual void Render(gef::Platform &platform, gef::SpriteRenderer* spriteRenderer, gef::Renderer3D* renderer3D) = 0;
};

#endif
