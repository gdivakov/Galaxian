#pragma once
#include <SDL.h>
#include <vector>

#include "LevelManager.h"
#include "App.h"
#include "Spawner.h"
#include "Ship.h"
#include "Timer.h"
#include "Hood.h"

class LevelManager;
class Ship;
class Spawner;
class Hood;

class LevelBase {
public:
	typedef std::vector<Object*> ObjectPointers;
	bool isPaused;
	Spawner* spawner = NULL;
	Hood* hood = NULL;

	LevelBase(const App* p_system, LevelManager* p_controller);
	virtual ~LevelBase();

	Ship* getPlayer();
	Spawner* getSpawner() { return spawner; };
	void unload();
	void accelerate();
	void stopAcceleration();
	void quit();
	void registerListeners();
	void deregisterListeners();
	bool togglePaused();
	const App* getSystem() { return system; };
	void restart();
	Uint32 getTime() { return timer->getTicks(); }
	void pauseTimer() { timer->pause(); };
	bool getIsCompleted() { return isCompleted; };
	bool getIsAccelerated() { return isAccelerated; };
	bool getAcceleratedAt() { return acceleratedAt; };
	virtual void handleCompleted() = 0;
	virtual void load() = 0;
	virtual void handleTick() = 0;
protected:
	const App* system;
	SDL_Renderer* renderer;
	ObjectPointers eventListeners;
	ObjectPointers renderListeners;
	ObjectPointers objsToFree;
	LevelManager* controller;
	Timer* timer;
	int nextEnemyIdx = 0;
	bool isCompleted = false;
	bool isAccelerated = false;
	Uint32 acceleratedAt;

	virtual void initAudio() = 0;
};