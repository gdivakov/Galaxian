#include <iostream>
#include <SDL.h>

#include "Level1.h"
#include "Consts.h"
#include "ShipConsts.h"
#include "Hood.h"
#include "SoundConst.h"
#include "Spawner.h"

class Spawner;

Level1::Level1(const App* p_system, LevelManager* p_controller) 
: 
LevelBase(p_system, p_controller) 
{
	initAudio(); // Todo: move to basic class 
}

Level1::~Level1()
{
	bg = NULL;
}

void Level1::load() 
{
	initObjects();
	registerListeners();
}

void Level1::initObjects()
{
	bg = new DynamicBackground(renderer, LEVEL1_BG_PATH, this);
	spawner = new Spawner(this);
	Hood* hood = new Hood(this);

	spawner->spawnPlayer(); // Todo: Render player above other objects (add important renderListeners to loop)
	//spawner->spawnEnemy();
	//spawner->spawnEnemy();
	//spawner->spawnBoss();

	ObjectPointers initObjects = { bg, spawner, hood };

	eventListeners = initObjects;
	renderListeners = initObjects;
	objsToFree = initObjects;
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