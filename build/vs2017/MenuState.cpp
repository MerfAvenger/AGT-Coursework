#include "MenuState.h"



MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::Init(gef::Platform &platform)
{
	Run();
}

int MenuState::Update(gef::Platform &platform)
{
	return -1;
}

void MenuState::Cleanup()
{
}

void MenuState::Run()
{
	bool quitMenu = false;

	while (!quitMenu)
	{

	}
}