#include <iostream>
#include <SDL.h>

#include "Level1.h"
#include "Ship.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Background.h"
#include "Consts.h"
#include "ShipConsts.h"
#include "Hood.h"
#include "SoundConst.h"

ShipParams getShipParams(const Size* windowSize, const ShipType type);
std::vector<BezierCurve> getEnemyPathCurves();

void Level1::load() 
{
	ShipParams sonicParams = getShipParams(system->getWindowSize(), SONIC_A); // Todo: don't pass params, get it and save is from constructor
	ShipParams pirateParams = getShipParams(system->getWindowSize(), PIRATE_A); // Todo: rename mainScreen to Level1 class

	Background* backgroundLvl1 = new Background(renderer, "res/space.png", this);
	Hood* hood = new Hood(renderer, this, system);

	EnemyShip* pirate = new EnemyShip(
		system,
		this,
		pirateParams,
		//playerShip,
		getEnemyPathCurves()
	);

	PlayerShip* playerShip = new PlayerShip(
		system, 
		this, 
		sonicParams
	);

	playerShip->registerEnemyCollidable(pirate);
	pirate->registerEnemyCollidable(playerShip);

	// Prepare level audio
	initAudio();

	eventListeners = { backgroundLvl1, playerShip, pirate, hood };
	renderListeners = { backgroundLvl1, playerShip, pirate, hood };
	objsToFree = { backgroundLvl1, playerShip, pirate, hood };

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

	audioPlayer->loadMusic("res/lvl1.mp3");
	audioPlayer->playMusic();
}

ShipParams getShipParams(const Size* windowSize, const ShipType type)
{
	switch (type)
	{
		case SONIC_A:
			return { 
				SONIC_A_SHIP, 
				SONIC_A_SHIP_EXPLOSION, 
				ROCKET, 
				SONIC_A_SPEED, 
				SONIC_A_COLLIDERS_DEFAULT, 
				GAME_OVER_SOUND 
			};
		case PIRATE_A:
			return { 
				PIRATE_A_SHIP, 
				PIRATE_A_SHIP_EXPLOSION, 
				ROCKET, 
				PIRATE_A_SPEED, 
				PIRATE_A_COLLIDERS_DEFAULT, 
				PIRATE_EXPLOSION_SOUND 
			};
	}
}

std::vector<BezierCurve> getEnemyPathCurves()
{
	std::vector<BezierCurve> curves;

	curves.push_back({ Vector2(100, 10), Vector2(350, 60), Vector2(350, 160), Vector2(300, 260) });
	curves.push_back({ Vector2(300, 260), Vector2(600, 700), Vector2(500, 300), Vector2(600, 600) });
	//curves.push_back({ Vector2(600, 600), Vector2(400, 200), Vector2(100, 100), Vector2(500, 300) });

	return curves;
}