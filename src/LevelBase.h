#pragma once
#include <SDL.h>
#include <vector>

#include "LevelManager.h"
#include "App.h"
#include "Spawner.h"
#include "Ship.h"

class LevelManager;
class Ship;
class Spawner;

class LevelBase {
public:
	typedef std::vector<Object*> ObjectPointers;
	bool isPaused;
	Spawner* spawner;

	LevelBase(const App* p_system, LevelManager* p_controller, Spawner* p_spawner)
	: 
	system(p_system),
	renderer(system->getRenderer()),
	controller(p_controller),
	isPaused(false),
	spawner(p_spawner) {};

	virtual ~LevelBase() { unload(); };
	virtual void load() = 0;
	virtual void initAudio() = 0;
	virtual void accelerate() = 0;

	Ship* getPlayer();
	Spawner* getSpawner() { return spawner; };
	void unload();
	void quit();
	void registerListeners();
	void deregisterListeners();
	bool togglePaused();
	const App* getSystem() { return system; };
protected:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
	ObjectPointers objsToFree;
	LevelManager* controller;
};