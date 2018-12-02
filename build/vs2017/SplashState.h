#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "BaseState.h"

namespace gef
{
	class ImageData;
	class Texture;
	class Sprite;
}

class SplashState : public BaseState
{
private:

	gef::ImageData* m_background;
	gef::Texture* m_bgTex;
	gef::Sprite* m_bgSprite;

	float m_splashTime; 
	const float MAX_SPLASH = 3.0f;

public:
	SplashState();
	~SplashState();

	void Init(gef::Platform &platform) override;

	int Update(gef::Platform &platform, float deltaTime) override;
	void Cleanup() override;
	void Render(gef::Platform &platform, gef::SpriteRenderer* spriteRenderer, gef::Renderer3D* renderer3D) override;
};

#endif

