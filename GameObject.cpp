#include "GameObject.h"



GameObject::GameObject()
{
}

GameObject::GameObject(gef::Vector4 position, gef::Mesh* mesh, char* tag)
{
	SetPosition(position);
	set_mesh(mesh);
	m_tag = tag;
}

gef::Vector4 GameObject::GetPositionFromTransform()
{
	gef::Vector4 position = transform_.GetRow(3);
	return position;
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
