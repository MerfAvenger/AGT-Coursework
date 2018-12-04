#ifndef WORLD_H
#define WORLD_H
#include "maths/vector4.h"
#include <vector>
#include <list>
#include "graphics/scene.h"
#include "Creature.h"

class World
{
private:

	gef::Mesh* GetFirstMesh(gef::Scene* scene, gef::Platform &platform);

	gef::Vector4 AABBMaxVertexToWorldPosition(GameObject obj);
	gef::Vector4 AABBMinVertexToWorldPosition(GameObject obj);
	bool AABB(GameObject obj1, GameObject obj2);

	gef::Scene* modelScene;
	Creature* player;
	std::vector<GameObject*> m_worldObjects;
	std::list<gef::Mesh*> meshReference;

public:
	World(gef::Platform& platform);
	~World();
	void Init(gef::Platform& platform);

	gef::Mesh* InitMesh(const char* fileName, gef::Scene* scene, gef::Platform& platform);

	bool CheckCollisions(gef::Vector4 newPosition, char* tag);

	const std::vector<GameObject*> WorldObjects() { return m_worldObjects; }
	Creature* Player() { return player; }

};

#endif
