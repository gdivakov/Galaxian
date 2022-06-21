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
	PlayerShip* player = (PlayerShip*) spawner->getPlayer();

	if (!player) 
	{
		return;
	}

	int passedMiles = player->getMilesPassed();

	if (nextEnemyIdx < enemiesToSpawn.size() &&
		enemiesToSpawn[nextEnemyIdx].milesToSpawn <= passedMiles)
	{
		if (!player->getIsAccelerated()) 
		{
			spawner->spawnEnemy(enemiesToSpawn[nextEnemyIdx].type); // Don't spawn enemies if player is accelerating (Todo: change for the boss spawn)
		}

		nextEnemyIdx++;
	}

}

void Level1::initObjects()
{
	bg = new DynamicBackground(renderer, LEVEL1_BG_PATH, this);
	spawner = new Spawner(this);
	Hood* hood = new Hood(this);

	spawner->spawnPlayer(); // Todo: Render player above other objects (add important renderListeners to loop)

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
	bg->accelerate();
	spawner->accelerateEnemies();
}