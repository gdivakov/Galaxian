#include <iostream>
#include <SDL.h>

#include "Level1.h"
#include "Ship.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "DynamicBackground.h"
#include "Consts.h"
#include "ShipConsts.h"
#include "Hood.h"
#include "SoundConst.h"

void Level1::load() 
{
	initObjects();
	initAudio();

	registerListeners();
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

void Level1::initObjects()
{
	DynamicBackground* bg = new DynamicBackground(renderer, LEVEL1_BG_PATH, this);
	Hood* hood = new Hood(this);
	PlayerShip* player = createPlayerShip();
	EnemyShip* enemy = createEnemyShip(player);
	EnemyShip* enemy2 = createEnemyShip(player);

	setPlayer(player);

	ObjectPointers initObjects = { 
		bg, 
		player,
		enemy,
		enemy2,
		hood,
	};

	eventListeners = initObjects;
	renderListeners = initObjects;
	objsToFree = initObjects;
}

PlayerShip* Level1::createPlayerShip()
{
	return new PlayerShip(system, this, SONIC_A);
}

EnemyShip* Level1::createEnemyShip(PlayerShip* target)
{
	EnemyShip* enemy = new EnemyShip(system, this, PIRATE_A, target, getEnemyPathCurves(enemiesSpawned));

	enemiesSpawned++;

	target->registerEnemyCollidable(enemy);
	enemy->registerEnemyCollidable(target);

	return enemy;
}