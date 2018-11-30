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
	m_currentState = splash;
	m_lastState = m_currentState;

	m_state = Morph(m_currentState, platform);
}

StateManager::~StateManager()
{
}

void StateManager::StateUpdate(gef::Platform &platform)
{
	if (m_lastState != m_currentState)
	{
		m_state = Morph(m_currentState, platform);
	}
		
}
