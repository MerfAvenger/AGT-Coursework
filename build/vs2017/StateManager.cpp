#include "StateManager.h"
#include "SplashState.h"
//#include "MenuState.h"
#include "GameState.h"
#include "system/platform.h"


BaseState* StateManager::Morph(APPLICATION_STATE newState, gef::Platform &platform)
{
	BaseState* newBaseState;

	switch (newState)
	{
	case splash:
		newBaseState = new SplashState();
		newBaseState->Init(platform);
		return newBaseState;
	case menu:
		//newBaseState = new MenuState();
		//static_cast<MenuState*>(newBaseState)->Init(platform);
		//return newBaseState;
		return NULL;
	case game:
		newBaseState = new GameState();
		newBaseState->Init(platform);
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
}

StateManager::~StateManager()
{
	m_state->~BaseState();
	delete m_state;
	m_state = nullptr;
}

int StateManager::Update(gef::Platform &platform, float deltaTime)
{
	return m_state->Update(platform, deltaTime);
}

void StateManager::Render(gef::Platform & platform, gef::SpriteRenderer * spriteRenderer, gef::Renderer3D * renderer3D)
{
	m_state->Render(platform, spriteRenderer, renderer3D);
}

void StateManager::SetState(APPLICATION_STATE state)
{
	m_currentState = state;
}

void StateManager::StateUpdate(gef::Platform &platform, gef::SpriteRenderer *spriteRenderer, gef::Renderer3D * renderer3D)
{

	if (m_lastState != m_currentState)
	{
		//Set up appropriate child state if the state has changed
		m_state = Morph(m_currentState, platform);

		if (m_currentState == game)
			static_cast<GameState*>(m_state)->SetupLights(renderer3D);

		m_lastState = m_currentState;
	}	

}
