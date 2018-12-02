#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "BaseState.h"

//Forward declerations
class BaseState;
enum APPLICATION_STATE;

class StateManager
{
private:
	

	BaseState* Morph(APPLICATION_STATE newState, gef::Platform &platform);

	APPLICATION_STATE m_currentState;
	APPLICATION_STATE m_lastState;

	BaseState* m_state;

public:

	StateManager(gef::Platform &platform);
	~StateManager();
	int Update(gef::Platform &platform, float deltaTime);
	void Render(gef::Platform &platform, gef::SpriteRenderer * spriteRenderer, gef::Renderer3D * renderer3D);

	void SetState(APPLICATION_STATE state);

	void StateUpdate(gef::Platform &platform, gef::SpriteRenderer * spriteRenderer, gef::Renderer3D * renderer3D);

};

#endif
