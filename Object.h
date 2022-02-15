#pragma once
#include <SDl.h>

class Object
{
public:
	virtual void onBeforeRender() {};
	virtual void onAfterRender() {};
	virtual void handleEvent(SDL_Event& e) = 0;
};