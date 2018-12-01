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
	InitRendering(platform);

	InitFont(platform);
}

void SplashState::InitRendering(gef::Platform &platform)
{
	m_spriteRenderer = gef::SpriteRenderer::Create(platform);
	m_imageLoader = new gef::PNGLoader();
	m_background = new gef::ImageData();
	m_bgSprite = new gef::Sprite();

	m_imageLoader->Load("splashTest.png", platform, *m_background);
	
	if (m_background)
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

int SplashState::Update(gef::Platform &platform, float deltaTime)
{
	int returnValue = 3;

	return returnValue;
}

void SplashState::Cleanup()
{
}

void SplashState::Render(gef::Platform &platform)
{
	//m_spriteRenderer->set_projection_matrix(platform.PerspectiveProjectionFov(camera_fov_, (float)platform.width() / (float)platform.height(), near_plane_, far_plane_));

	m_spriteRenderer->Begin(false);

	m_spriteRenderer->DrawSprite(*m_bgSprite);

	m_spriteRenderer->End();
}