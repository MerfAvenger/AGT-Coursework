#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "graphics/mesh_instance.h"

class GameObject : public gef::MeshInstance
{
protected:

	gef::Vector4 GetPositionFromTransform()
	{
		gef::Vector4 position = transform_.GetRow(3);
		return position;
	}
	void UpdateTransformFromVectorPosition(gef::Vector4 position);

public:
	GameObject();
	GameObject(gef::Vector4 position, gef::Mesh* mesh);
	~GameObject();

	void SetPosition(gef::Vector4 newPosition) { UpdateTransformFromVectorPosition(newPosition); }
	gef::Vector4 GetPosition() { return GetPositionFromTransform(); }
};

#endif