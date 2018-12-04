#include "Creature.h"
#include "graphics/mesh.h"
#include "World.h"



Creature::Creature(gef::Vector4 position, gef::Mesh* mesh, float health, char* tag) : GameObject(position, mesh, tag)
{
	m_health = health;
}


Creature::~Creature()
{
}

void Creature::Move(gef::Vector4 moveDirection, World* world, float deltaTime)
{
	gef::Vector4 newPosition = GetPosition() + (moveDirection * SPEED * deltaTime);

	if(world->CheckCollisions(newPosition, m_tag))
	{
		SetPosition(newPosition);
	}
}
