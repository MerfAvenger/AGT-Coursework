#pragma once
#include "BaseState.h"
#include "World.h"

namespace gef
{
	class Renderer3D;
	class SpriteRenderer;
	class InputManager;
	class Font;	
}

class GameState : public BaseState
{
private:
	float fps_;

	gef::Vector4 camera_eye_;
	gef::Vector4 camera_lookat_;
	gef::Vector4 camera_up_;
	float camera_fov_;
	float near_plane_;
	float far_plane_;

	World* m_world;

	void CleanUpFont(gef::Font* font);
public:
	GameState();
	~GameState();

	void Init(gef::Platform &platform) override;
	void DrawHUD(gef::Font* font, gef::SpriteRenderer* spriteRenderer);
	void SetupLights(gef::Renderer3D* renderer3D);
	void SetupCamera();
	int Update(gef::Platform &platform, float deltaTime) override;
	void Render(gef::Platform &platform, gef::SpriteRenderer* spriteRenderer, gef::Renderer3D* renderer3D);
};

