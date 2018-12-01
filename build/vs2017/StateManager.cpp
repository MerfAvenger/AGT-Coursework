#include "StateManager.h"
#include "SplashState.h"
#include "MenuState.h"
#include "GameState.h"
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
	case game:
		newBaseState = new GameState();
		static_cast<MenuState*>(newBaseState)->Init(platform);
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

int StateManager::Update(gef::Platform &platform, float deltaTime)
{
	return m_state->Update(platform, deltaTime);
}

void StateManager::Render(gef::Platform & platform)
{
	m_state->Render(platform);
}

void StateManager::StateUpdate(gef::Platform &platform)
{

	if (m_lastState != m_currentState)
	{
		gef::SpriteRenderer* renderer;
		gef::Font* font;

		if (m_currentState == game && m_lastState == splash)
		{
			renderer = static_cast<SplashState*>(m_state)->passRenderer();
			font = static_cast<SplashState*>(m_state)->passFonts();
		}
		//Set up appropriate child state if the state has changed
		m_state = Morph(m_currentState, platform);

		if (font && renderer)
		{
			static_cast<GameState*>(m_state)->PassRenderer(renderer, font);
		}

		m_lastState = m_currentState;
	}	

}
