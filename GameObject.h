#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "graphics/mesh_instance.h"
#include <string>

class GameObject : public gef::MeshInstance
{
protected:

	char* m_tag;

	gef::Vector4 GetPositionFromTransform();
	void UpdateTransformFromVectorPosition(gef::Vector4 position);

public:
	GameObject();
	GameObject(gef::Vector4 position, gef::Mesh* mesh, char* tag);
	~GameObject();

	char* Tag() { return m_tag; }
	void SetPosition(gef::Vector4 newPosition) { UpdateTransformFromVectorPosition(newPosition); }
	gef::Vector4 GetPosition() { return GetPositionFromTransform(); }
};

#endif