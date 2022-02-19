#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"

class Level {
public: 
	typedef std::vector<Object*> ObjectPointers;
	Level(const App* system);
	~Level();
	void start();
private:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
};