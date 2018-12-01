#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "BaseState.h"
class MenuState : public BaseState
{
private:
	void Run();

public:
	MenuState();
	~MenuState();

	void Init(gef::Platform &platform) override;
	int Update(gef::Platform &platform, float deltaTime) override;
	void Cleanup() override;
};

#endif