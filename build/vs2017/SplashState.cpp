#include "SplashState.h"
#include "graphics/sprite_renderer.h"
#include "graphics/font.h"
#include "assets/png_loader.h"
#include "graphics/image_data.h"
#include "graphics/texture.h"
#include "graphics/sprite.h"


SplashState::SplashState()
{
}


SplashState::~SplashState()
{
}

void SplashState::Init(gef::Platform &platform)
{
	InitRendering(platform);

	InitFont(platform);

	Update();
}

void SplashState::InitRendering(gef::Platform & platform)
{
	m_spriteRenderer = gef::SpriteRenderer::Create(platform);
	m_imageLoader = new gef::PNGLoader();
	m_background = new gef::ImageData();
	m_bgSprite = new gef::Sprite();

	m_imageLoader->Load("splashTest.png", platform, *m_background);
	
	if (m_background);
	{
		m_bgTex = gef::Texture::Create(platform, *m_background);

		m_bgSprite->set_height(544.0f);
		m_bgSprite->set_width(900.0f);
		m_bgSprite->set_position(0.0f, 0.0f, 0.0f);
		m_bgSprite->set_texture(m_bgTex);
	}
}

void SplashState::InitFont(gef::Platform &platform)
{
	m_font = new gef::Font(platform);
	m_font->Load("comic_sans");
}

void SplashState::Update()
{
	bool cont = true;

	while (cont)
	{
		Render();
	}
}

void SplashState::Cleanup()
{
}

void SplashState::Render()
{
	m_spriteRenderer->Begin();

	m_spriteRenderer->DrawSprite(*m_bgSprite);

	m_spriteRenderer->End();
}