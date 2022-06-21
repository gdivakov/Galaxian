#pragma once
#include <SDL.h>
#include <vector>

#include "LevelManager.h"
#include "App.h"
#include "Spawner.h"
#include "Ship.h"
#include "Timer.h"

class LevelManager;
class Ship;
class Spawner;

class LevelBase {
public:
	typedef std::vector<Object*> ObjectPointers;
	bool isPaused;
	Spawner* spawner = NULL;

	LevelBase(const App* p_system, LevelManager* p_controller);
	virtual void load() = 0;
	virtual void accelerate() = 0; // Todo: rename
	virtual void handleTick() = 0;
	virtual ~LevelBase();

	Ship* getPlayer();
	Spawner* getSpawner() { return spawner; };
	void unload();
	void quit();
	void registerListeners();
	void deregisterListeners();
	bool togglePaused();
	const App* getSystem() { return system; };
	void restart();
	Uint32 getTime() { return timer->getTicks(); }
protected:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
	ObjectPointers objsToFree;
	LevelManager* controller;
	int nextEnemyIdx = 0;
	Timer* timer;
	virtual void initAudio() = 0;
};