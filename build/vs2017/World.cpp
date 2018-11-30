#include "World.h"
#include "graphics/mesh.h"


World::World(gef::Platform &platform)
{
	Init(platform);
}


World::~World()
{
}

void World::Init(gef::Platform &platform)
{
	meshReference.push_back(InitMesh("ball1.scn", modelScene, platform));
	m_worldObjects.emplace_back(GameObject(gef::Vector4(0.0f, 0.0f, 0.0f), meshReference.back()));

	//Keep track of the player
	player = new GameObject();
	*player = m_worldObjects.at(0);

	//Add additional world objects
	meshReference.push_back(InitMesh("ball2.scn", modelScene, platform));
	m_worldObjects.emplace_back(GameObject(gef::Vector4(0.0f, 0.0f, 150.0f), meshReference.back()));
}

gef::Mesh* World::InitMesh(const char* fileName, gef::Scene* scene, gef::Platform &platform)
{
	//Reset loader scene data to ensure no overwrites
	modelScene = new gef::Scene();

	//Read scene file data
	modelScene->ReadSceneFromFile(platform, fileName);

	modelScene->CreateMaterials(platform);
	return GetFirstMesh(modelScene, platform);
}

gef::Mesh* World::GetFirstMesh(gef::Scene* scene, gef::Platform &platform)
{
	gef::Mesh* mesh = NULL;

	if (scene)
	{
		if (scene->mesh_data.size() > 0)
			mesh = modelScene->CreateMesh(platform, scene->mesh_data.front());
	}

	return mesh;
}

bool World::CheckCollisions(gef::Vector4 newPosition)
{
	if(m_worldObjects.size() > 1)
	{
		for(UInt16 i = 0; i < m_worldObjects.size() - 1; i++)
		{
			for(int c = i + 1; c < m_worldObjects.size(); c++)
			{
				return AABB(m_worldObjects[i], m_worldObjects[c]);
			}
		}
	}

	return true;
}

bool World::AABB(GameObject obj1, GameObject obj2)
{

	return(
		AABBMinVertexToWorldPosition(obj1).x() < AABBMaxVertexToWorldPosition(obj2).x() &&
		AABBMinVertexToWorldPosition(obj1).y() < AABBMaxVertexToWorldPosition(obj2).y() &&
		AABBMinVertexToWorldPosition(obj1).z() < AABBMaxVertexToWorldPosition(obj2).z() &&
		AABBMaxVertexToWorldPosition(obj1).x() > AABBMinVertexToWorldPosition(obj2).x() &&
		AABBMaxVertexToWorldPosition(obj1).y() > AABBMinVertexToWorldPosition(obj2).y() &&
		AABBMaxVertexToWorldPosition(obj1).z() > AABBMinVertexToWorldPosition(obj2).z()
		);
}

gef::Vector4 World::AABBMaxVertexToWorldPosition(GameObject obj)
{
	return gef::Vector4(
		obj.GetPosition().x() + obj.mesh()->aabb().max_vtx().x(),
		obj.GetPosition().y() + obj.mesh()->aabb().max_vtx().y(),
		obj.GetPosition().z() + obj.mesh()->aabb().max_vtx().z()
	);
}

gef::Vector4 World::AABBMinVertexToWorldPosition(GameObject obj)
{
	return gef::Vector4(
		obj.GetPosition().x() + obj.mesh()->aabb().min_vtx().x(),
		obj.GetPosition().y() + obj.mesh()->aabb().min_vtx().y(),
		obj.GetPosition().z() + obj.mesh()->aabb().min_vtx().z()
	);
}
