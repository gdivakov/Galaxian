#include <iostream>
#include <SDL.h>

#include "Level1.h"
#include "Ship.h"

#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Background.h"
#include "Consts.h"

ShipParams getShipParams(const Size* windowSize, const ShipType type);
std::vector<BezierCurve> getEnemyPathCurves();

// Todo: 
// 1. Select ship before the game; ship should has params as [ health, armour, speed, weapon, buffs ]
// 2. Show dialog with the task description at the begining
// ---> 3. Create pause menu view and mechanism to stop the level
// 4. Hood should have: [ health, armour, buffs, score, weapon ]
// 5. Add joystick support
// 6. 2 players game support 
// 7. Fullscreen mode
// 8. Russian language
// 9. File saving progress and settings
// 10. More [ player ships, enemies, weapons, buffs, bosses, enemies behaviour logic ]
// 11. Score at the end of the level with achieved weapon

void Level1::load() 
{
	ShipParams sonicParams = getShipParams(system->getWindowSize(), SONIC_A);
	ShipParams pirateParams = getShipParams(system->getWindowSize(), PIRATE_A);

	Background* backgroundLvl1 = new Background(renderer, "res/space.png");
	PlayerShip* playerShip = new PlayerShip(system, "res/shipA.png", sonicParams);
	EnemyShip* pirate = new EnemyShip(system, "res/pirateA.png", pirateParams, playerShip);

	// Prepare level audio
	Audio* audioPlayer = system->getAudioPlayer();
	audioPlayer->loadMusic("res/lvl1.mp3");
	audioPlayer->playMusic(); 

	eventListeners = { backgroundLvl1, playerShip, audioPlayer, pirate };
	renderListeners = { backgroundLvl1, playerShip, pirate };
	objsToFree = { backgroundLvl1, playerShip, pirate };

	registerListeners();
}

ShipParams getShipParams(const Size* windowSize, const ShipType type)
{
	SpriteParams spriteParams;
	SDL_Point pos;
	ShipParams params;

	switch (type)
	{
		case SONIC_A:
			spriteParams = SONIC_A_SHIP;
			params.maxVelocity = SONIC_A_VELOCITY;
			params.gunType = ROCKET;
			pos = { (windowSize->w - spriteParams.imageW) / 2, windowSize->h - spriteParams.imageH };
			break;
		case PIRATE_A:
			spriteParams = PIRATE_A_SHIP;
			params.maxVelocity = PIRATE_A_VELOCITY;
			params.gunType = ROCKET; // Todo: change 
			pos = { (windowSize->w - spriteParams.imageW) / 4, spriteParams.imageH };
			params.pathCurves = getEnemyPathCurves(); // to do: edit this => create function to set up all level enemies
			break;
	}

	Size shipSize = { spriteParams.imageW, spriteParams.imageH };

	params.type = type;
	params.sprite = spriteParams;
	params.rect = { pos.x, pos.y, shipSize.w, shipSize.h };

	return params;
}

std::vector<BezierCurve> getEnemyPathCurves()
{
	std::vector<BezierCurve> curves;

	curves.push_back({ Vector2(100, 10), Vector2(350, 60), Vector2(350, 160), Vector2(300, 260) });
	curves.push_back({ Vector2(300, 260), Vector2(600, 700), Vector2(500, 300), Vector2(600, 600) });
	//curves.push_back({ Vector2(600, 600), Vector2(400, 200), Vector2(100, 100), Vector2(500, 300) });

	return curves;
}