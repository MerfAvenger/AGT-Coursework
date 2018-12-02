#include "SplashState.h"
#include "graphics/sprite_renderer.h"
#include "graphics/font.h"
#include "assets/png_loader.h"
#include "graphics/image_data.h"
#include "graphics/texture.h"
#include "graphics/sprite.h"
#include "system/platform.h"
#include "maths/math_utils.h"


SplashState::SplashState()
{
}


SplashState::~SplashState()
{
}

void SplashState::Init(gef::Platform &platform)
{
	m_splashTime = 0.0f;

	m_imageLoader = new gef::PNGLoader();
	m_background = new gef::ImageData();
	m_bgSprite = new gef::Sprite();

	m_imageLoader->Load("splashTest.png", platform, *m_background);

	if (m_background)
	{
		m_bgTex = gef::Texture::Create(platform, *m_background);

		m_bgSprite->set_height(544.0f);
		m_bgSprite->set_width(900.0f);
		m_bgSprite->set_position(m_bgSprite->width() / 2, m_bgSprite->height() / 2, 0.0f);
		m_bgSprite->set_texture(m_bgTex);
	}
}

int SplashState::Update(gef::Platform &platform, float deltaTime)
{
	m_splashTime += deltaTime;

	if (m_splashTime >= MAX_SPLASH)
	{
		return 3;
	}

	return 0;
}

void SplashState::Cleanup()
{
}

void SplashState::Render(gef::Platform &platform, gef::SpriteRenderer* spriteRenderer, gef::Renderer3D* renderer3D)
{
	spriteRenderer->Begin(false);

	spriteRenderer->DrawSprite(*m_bgSprite);

	spriteRenderer->End();
}