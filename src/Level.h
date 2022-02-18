#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"

class Level {
public: 
	typedef std::vector<Object*> ObjectPointers;
	Level(App* system);
	~Level();
	void start();
private:
	App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
};