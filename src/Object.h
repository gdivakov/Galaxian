#pragma once
#include <SDl.h>
#include <iostream>

class Object
{
public:
	virtual ~Object() {};
	virtual void free() {};
	virtual void onBeforeRender() {};
	virtual void onAfterRender() {};
	virtual void handleEvent(SDL_Event& e) = 0;
};