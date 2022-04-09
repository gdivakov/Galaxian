#pragma once
#include <SDL.h>
#include <vector>

#include "LevelManager.h"
#include "App.h"

class LevelManager;

class LevelBase {
public:
	typedef std::vector<Object*> ObjectPointers;
	bool isPaused;
	LevelBase(const App* p_system, LevelManager* p_controller)
		: system(p_system), 
		renderer(system->getRenderer()),
		controller(p_controller),
		isPaused(false)
	{};
	virtual ~LevelBase() { unload(); }
	virtual void load() = 0;
	void unload();
	void quit();
	void registerListeners();
	void deregisterListeners();
	bool togglePaused() { isPaused = !isPaused; return isPaused; };
	void removeObject(Object* object);
protected:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
	ObjectPointers objsToFree;
	LevelManager* controller;
};