#include <iostream>
#include <SDL.h>

#include "Level.h"
#include "Ship.h"
#include "Background.h"
#include "Consts.h"

Level::Level(App* p_system)
{

	renderer = p_system->getRenderer();
	system = p_system;
}

Level::~Level()
{
	renderer = NULL;
	system = NULL;
	// Todo: Remove event/render listeners from event loop
}

void Level::start()
{
	// Prepare level objects
	ShipParams playerShipParams = { DEFAULT_PLAYER_SHIP_SPRITE_PARAMS, ROCKET };
	Audio* audioPlayer = system->getAudioPlayer();
	Loop* gameLoop = system->getGameLoop();

	Background backgroundLvl1(renderer, "res/space.png");
	Ship playerShip(system, "res/shipA.png", playerShipParams);

	// Prepare level audio
	audioPlayer->load("res/lvl1.mp3");
	//audioPlayer->play(); 

	eventListeners = { &backgroundLvl1, &playerShip, audioPlayer };
	renderListeners = { &backgroundLvl1, &playerShip };

	gameLoop->addEventListeners(eventListeners);
	gameLoop->addRenderListeners(renderListeners);
	gameLoop->start();
}