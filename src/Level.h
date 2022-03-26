#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"

class Level {
public:
	typedef std::vector<Object*> ObjectPointers;
	Level(const App* p_system) : system(p_system), renderer(system->getRenderer()) {};
	virtual ~Level() { renderer = NULL; system = NULL; };
	virtual void start() = 0;
protected:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
};