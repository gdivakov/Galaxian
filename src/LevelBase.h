#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"

class LevelBase {
public:
	typedef std::vector<Object*> ObjectPointers;
	LevelBase(const App* p_system) : system(p_system), renderer(system->getRenderer()) {};
	virtual ~LevelBase() { unload(); }
	
	virtual void load() = 0;
	void unload();

	void registerListeners();
	void deregisterListeners();
protected:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
	ObjectPointers objsToFree;
};