#pragma once
#include "BaseState.h"
#include "World.h"
#include <platform/vita/graphics/texture_vita.h>

namespace gef
{
	class Renderer3D;
	class SpriteRenderer;
	class InputManager;
	class Font;	
	class AppData;
	class RenderTarget;
	class Sprite;
}

class GameState : public BaseState
{
private:
	float fps_;

	gef::Vector4 camera_eye_;
	gef::Vector4 camera_lookat_;
	gef::Vector4 camera_up_;
	float camera_fov_;
	const float near_plane_ = 0.01f;
	const float far_plane_ = 100.0f;

	//Camera variables
	gef::Sprite* m_cameraSprite;
	gef::Matrix44 m_cameraOrthoMatrix;
	gef::TextureVita m_cameraTexture;

	gef::Matrix44 m_FOVProjectionMatrix, m_scaleMatrix, m_finalProjectionMatrix, m_localMatrix;

	gef::Matrix44 m_cameraOrientedOrthoMatrix;

	float m_vScale;
	float m_hScale;

	World* m_world;

	void CleanUpFont(gef::Font* font);
	void RenderOverlay(gef::Platform &platform, gef::SpriteRenderer* renderer);

	void InitCamera(gef::Platform &platform);

public:
	GameState();
	~GameState();

	void Init(gef::Platform &platform) override;
	void Cleanup() override;
	void DrawHUD(gef::Font* font, gef::SpriteRenderer* spriteRenderer);
	void SetupLights(gef::Renderer3D* renderer3D);
	void SetupGameCamera();
	int Update(gef::Platform &platform, float deltaTime) override;
	void Render(gef::Platform &platform, gef::SpriteRenderer* spriteRenderer, gef::Renderer3D* renderer3D);
};

