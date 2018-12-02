#include "BaseState.h"


int BaseState::Update(gef::Platform &platform, float deltaTime)
{
	return -1;
}

void BaseState::Cleanup()
{
}

BaseState::BaseState()
{
}


BaseState::~BaseState()
{
	Cleanup();
}

