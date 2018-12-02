#pragma once
#include "GameObject.h"

class World;
class Creature :
	public GameObject
{
private:
	float m_health;
	const float SPEED = 1000.0f;
public:
	Creature(gef::Vector4 position, gef::Mesh* mesh, float health, char* tag);
	~Creature();

	void Move(gef::Vector4 moveDirection, World* world, float deltaTime);
};

