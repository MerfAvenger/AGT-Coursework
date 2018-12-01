#ifndef BASESTATE_H
#define BASESTATE_H
#include "maths/vector4.h"

enum APPLICATION_STATE
{
	def,
	splash,
	menu,
	game,
	pause
};

namespace gef
{
	class Platform;
}

class BaseState
{

protected:
	virtual void Init(gef::Platform &platform);
	virtual void InitRendering(gef::Platform &platform);
	
	virtual void Cleanup();
	


public:
	BaseState();
	~BaseState();

	virtual int Update(gef::Platform &platform, float deltaTime);
	virtual void Render(gef::Platform &platform);
};

#endif
