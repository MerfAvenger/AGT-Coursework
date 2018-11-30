#ifndef WORLD_H
#define WORLD_H
#include "maths/vector4.h"
#include "GameObject.h"
#include <vector>
#include <list>
#include "graphics/scene.h"

class World
{
public:
	World(gef::Platform& platform);
	~World();
	void Init(gef::Platform& platform);

	gef::Mesh* InitMesh(const char* fileName, gef::Scene* scene, gef::Platform& platform);

	bool CheckCollisions(gef::Vector4 newPosition);

	const std::vector<GameObject> WorldObjects() { return m_worldObjects; }
	GameObject* Player() { return player; }

private:

	gef::Mesh* GetFirstMesh(gef::Scene* scene, gef::Platform &platform);

	gef::Vector4 AABBMaxVertexToWorldPosition(GameObject obj);
	gef::Vector4 AABBMinVertexToWorldPosition(GameObject obj);
	bool AABB(GameObject obj1, GameObject obj2);

	gef::Scene* modelScene;
	GameObject* player;
	std::vector<GameObject> m_worldObjects;
	std::list<gef::Mesh*> meshReference;

};

#endif
