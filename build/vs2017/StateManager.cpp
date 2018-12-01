#include "StateManager.h"
#include "SplashState.h"
#include "MenuState.h"
#include "system/platform.h"


BaseState* StateManager::Morph(APPLICATION_STATE newState, gef::Platform &platform)
{
	BaseState* newBaseState = new BaseState();

	switch (newState)
	{
	case splash:
		newBaseState = new SplashState();
		static_cast<SplashState*>(newBaseState)->Init(platform);
		return newBaseState;
	case menu:
		newBaseState = new MenuState();
		static_cast<MenuState*>(newBaseState)->Init(platform);
		return newBaseState;
	case def:
		return nullptr;
	default:
		return nullptr;
	}
}

StateManager::StateManager(gef::Platform &platform)
{
	//Initialise states
	m_currentState = splash;
	m_lastState = def;

	//Begin update
	StateUpdate(platform);
}

StateManager::~StateManager()
{
	m_state->~BaseState();
	delete m_state;
	m_state = nullptr;
}

int StateManager::Update(gef::Platform &platform)
{
	return m_state->Update(platform);
}

void StateManager::Render(gef::Platform & platform)
{
	m_state->Render(platform);
}

void StateManager::StateUpdate(gef::Platform &platform)
{
	//while(returnValue != -1)
	{
		if (m_lastState != m_currentState)
		{
			//Set up appropriate child state if the state has changed
			m_state = Morph(m_currentState, platform);
		}	
	}	
}
