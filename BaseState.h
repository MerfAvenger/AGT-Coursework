#ifndef BASESTATE_H
#define BASESTATE_H

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
	
	gef::InputManager* inputManager;
	gef::PNGLoader* m_imageLoader;


public:
	BaseState();
	~BaseState();

	virtual void Cleanup() = 0;
	virtual void Init(gef::Platform &platform) = 0;
	virtual int Update(gef::Platform &platform, float deltaTime);
	virtual void Render(gef::Platform &platform, gef::SpriteRenderer* spriteRenderer, gef::Renderer3D* renderer3D) = 0;
};

#endif
