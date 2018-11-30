#ifndef BASESTATE_H
#define BASESTATE_H

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
private:

protected:
	virtual void Init(gef::Platform &platform);
	virtual void InitRendering(gef::Platform &platform);
	virtual void Update();
	virtual void Cleanup();
	virtual void Render();

public:
	BaseState();
	~BaseState();

};

#endif
