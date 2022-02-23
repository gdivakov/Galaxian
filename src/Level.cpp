#include <iostream>
#include <SDL.h>

#include "Level.h"
#include "Ship.h"

#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Background.h"
#include "Consts.h"

ShipParams getShipParams(const Size* windowSize, const ShipType type);

Level::Level(const App* p_system) : system(p_system), renderer(system->getRenderer())
{}

Level::~Level()
{
	Loop* gameLoop = system->getGameLoop();

	// Deregister level objects from loop
	gameLoop->removeEventListeners(eventListeners);
	gameLoop->removeRenderListeners(renderListeners);

	renderer = NULL;
	system = NULL;
}

void Level::start()
{
	// Prepare level objects
	ShipParams sonicParams = getShipParams(system->getWindowSize(), SONIC_A);
	ShipParams pirateParams = getShipParams(system->getWindowSize(), PIRATE_A);

	Audio* audioPlayer = system->getAudioPlayer();
	Loop* gameLoop = system->getGameLoop();

	Background backgroundLvl1(renderer, "res/space.png");

	PlayerShip playerShip(system, "res/shipA.png", sonicParams);
	EnemyShip pirate(system, "res/pirateA.png", pirateParams, playerShip);

	// Prepare level audio
	audioPlayer->loadMusic("res/lvl1.mp3");
	//audioPlayer->playMusic(); 

	eventListeners = { &backgroundLvl1, &playerShip, audioPlayer, &pirate };
	renderListeners = { &backgroundLvl1, &playerShip, &pirate };

	gameLoop->addEventListeners(eventListeners);
	gameLoop->addRenderListeners(renderListeners);
	gameLoop->start();
}

ShipParams getShipParams(const Size* windowSize, const ShipType type)
{
	SpriteParams spriteParams;
	GunType gun;
	int vel;
	SDL_Point pos;

	switch (type)
	{
		case SONIC_A:
			spriteParams = SONIC_A_SHIP;
			vel = SONIC_A_VELOCITY;
			gun = ROCKET;
			pos = { (windowSize->w - spriteParams.imageW) / 2, windowSize->h - spriteParams.imageH };
			break;
		case PIRATE_A:
			spriteParams = PIRATE_A_SHIP;
			vel = PIRATE_A_VELOCITY;
			gun = ROCKET; // Todo: change 
			pos = { (windowSize->w - spriteParams.imageW) / 4, spriteParams.imageH };
			break;
	}

	Size shipSize = { spriteParams.imageW, spriteParams.imageH };

	SDL_Rect rect = {
			pos.x, 
			pos.y,
			shipSize.w,
			shipSize.h,
	};

	ShipParams params = {
		type,
		spriteParams,
		gun,
		rect,
		vel,
	};

	return params;
}