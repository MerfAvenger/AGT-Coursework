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
	gef::Vector4 camera_eye_;
	gef::Vector4 camera_lookat_;
	gef::Vector4 camera_up_;
	float camera_fov_;
	float near_plane_;
	float far_plane_;

protected:
	virtual void Init(gef::Platform &platform);
	virtual void InitRendering(gef::Platform &platform);
	
	virtual void Cleanup();
	


public:
	BaseState();
	~BaseState();

	virtual int Update(gef::Platform &platform);
	virtual void Render(gef::Platform &platform);
};

#endif
