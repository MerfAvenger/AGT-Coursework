#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include "BaseState.h"

namespace gef
{
	class SpriteRenderer;
	class Font;
	class PNGLoader;
	class ImageData;
	class Texture;
	class Sprite;
}

class SplashState : public BaseState
{
private:
	gef::SpriteRenderer* m_spriteRenderer;
	gef::PNGLoader* m_imageLoader;
	gef::Font* m_font;

	gef::ImageData* m_background;
	gef::Texture* m_bgTex;
	gef::Sprite* m_bgSprite;

public:
	SplashState();
	~SplashState();

	void Init(gef::Platform &platform) override;
	void InitRendering(gef::Platform &platform) override;
	void InitFont(gef::Platform &platform);

	int Update(gef::Platform &platform, float deltaTime) override;
	void Cleanup() override;
	void Render(gef::Platform &platform) override;

	gef::Font* passFonts() { return m_font; }
	gef::SpriteRenderer* passRenderer() { return m_spriteRenderer; }
};

#endif

