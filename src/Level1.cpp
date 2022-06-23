#include <iostream>
#include <SDL.h>

#include "Level1.h"
#include "Consts.h"
#include "ShipConsts.h"
#include "Hood.h"
#include "SoundConst.h"
#include "Spawner.h"
#include "PlayerShip.h"

class Spawner;

Level1::Level1(const App* p_system, LevelManager* p_controller) 
: 
LevelBase(p_system, p_controller) 
{
	initAudio();
	isCompleted = false;
}

Level1::~Level1()
{
	bg = NULL;
}

void Level1::load() 
{
	initObjects();
	registerListeners();

	timer->restart();
}

void Level1::handleTick() // Todo: this logic should be relative to specific level spawner (create Level1Spawner : public Spawner)
{
	if (isAccelerated) // Update acceleration status
	{
		BuffParams params = getBuffParamsByType(BUFF_SPEED_UP);

		if (getTime() - acceleratedAt > params.duration)
		{
			stopAcceleration();
		}
	}

	PlayerShip* player = (PlayerShip*) getPlayer();

	if (player == nullptr || !player->isActive) 
	{
		return;
	}

	int passedMiles = player->getMilesPassed();

	bool isSpawnNewEnemy = nextEnemyIdx < enemiesToSpawn.size() &&
		enemiesToSpawn[nextEnemyIdx].milesToSpawn <= passedMiles;

	if (isSpawnNewEnemy)
	{
		if (!isAccelerated) // Don't spawn enemies level is accelerated
		{
			spawner->spawnEnemy(enemiesToSpawn[nextEnemyIdx].type);
		}

		nextEnemyIdx++;

		if (isAccelerated && nextEnemyIdx == enemiesToSpawn.size())
		{
			nextEnemyIdx--; // Boss should spawn after the acceleration is over
		}
	}

	bool isLastEnemyKilled = nextEnemyIdx == enemiesToSpawn.size()
		&& !spawner->getEnemies().size();

	if (isLastEnemyKilled && !isAccelerated && !isCompleted)
	{
		system->getAudioPlayer()->playSound(REACH_THE_FINISH);
		accelerate();
		isCompleted = true;
	}
}

void Level1::initObjects()
{
	bg = new DynamicBackground(renderer, LEVEL1_BG_PATH, this);
	spawner = new Spawner(this);
	hood = new Hood(this);

	// Todo: Render player above other objects (add important renderListeners to loop)
	spawner->spawnPlayer();

	ObjectPointers levelObjects = { bg, spawner, hood };

	eventListeners = levelObjects;
	renderListeners = levelObjects;
	objsToFree = levelObjects;
}

void Level1::initAudio()
{
	Audio* audioPlayer = system->getAudioPlayer();

	// Load level sounds
	for (int i = 0; i < LEVEL_1_SOUNDS.size(); i++)
	{
		audioPlayer->loadSound(LEVEL_1_SOUNDS[i]);
	}

	audioPlayer->loadMusic("res/audio/lvl1.mp3");
	audioPlayer->playMusic();
}

void Level1::accelerate()
{
	isAccelerated = true;
	acceleratedAt = getTime();

	spawner->accelerate();
}

void Level1::handleCompleted()
{
	pauseTimer();
	stopAcceleration();
	hood->showTotal();
}