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

	//Keep track of the player
	player = new Creature(gef::Vector4(0.0f, 0.0f, 0.0f),meshReference.back(), 100.0f, "pet" );
	m_worldObjects.push_back(player);

	//Add additional world objects
	meshReference.push_back(InitMesh("ball2.scn", modelScene, platform));
	m_worldObjects.push_back(new GameObject(gef::Vector4(0.0f, 0.0f, 250.0f), meshReference.back(), "ball"));
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

bool World::CheckCollisions(gef::Vector4 newPosition, char* tag)
{
	GameObject searchObject;

	for (GameObject* worldObject : m_worldObjects)
	{
		if (worldObject->Tag() == tag)
		{
			searchObject = *worldObject;
			break;
		}
	}

	searchObject.SetPosition(searchObject.GetPosition() + newPosition);

	for (GameObject* worldObject : m_worldObjects)
	{
		if(worldObject->Tag() != tag)
		{
			if(AABB(searchObject, *worldObject))
			{
				return false;
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
