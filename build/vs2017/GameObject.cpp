#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(gef::Vector4 position, gef::Mesh* mesh)
{
	SetPosition(position);
	set_mesh(mesh);
}

void GameObject::UpdateTransformFromVectorPosition(gef::Vector4 position)
{
	gef::Matrix44 tempMatrix = this->transform();
	tempMatrix.SetTranslation(position);

	set_transform(tempMatrix);
}

GameObject::~GameObject()
{
}
