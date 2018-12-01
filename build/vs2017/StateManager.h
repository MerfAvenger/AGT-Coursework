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
	int Update(gef::Platform &platform);
	void Render(gef::Platform &platform);

	void StateUpdate(gef::Platform &platform);

};

#endif
