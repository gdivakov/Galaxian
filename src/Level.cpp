#include <iostream>
#include <SDL.h>

#include "Level.h"
#include "Ship.h"
#include "Background.h"
#include "Consts.h"

ShipParams getInitPlayerParams(const Size* windowSize);

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
	ShipParams playerParams = getInitPlayerParams(system->getWindowSize());
	Audio* audioPlayer = system->getAudioPlayer();
	Loop* gameLoop = system->getGameLoop();

	Background backgroundLvl1(renderer, "res/space.png");
	Ship playerShip(system, "res/shipA.png", playerParams);

	// Prepare level audio
	audioPlayer->load("res/lvl1.mp3");
	//audioPlayer->play(); 

	eventListeners = { &backgroundLvl1, &playerShip, audioPlayer };
	renderListeners = { &backgroundLvl1, &playerShip };

	gameLoop->addEventListeners(eventListeners);
	gameLoop->addRenderListeners(renderListeners);
	gameLoop->start();
}

ShipParams getInitPlayerParams(const Size* windowSize)
{
	Size shipSize = { DEFAULT_PLAYER_SHIP_SPRITE_PARAMS.imageW, DEFAULT_PLAYER_SHIP_SPRITE_PARAMS.imageH };

	SDL_Rect shipRect = {
			(windowSize->w - shipSize.w) / 2,
			windowSize->h - shipSize.h,
			shipSize.w,
			shipSize.h,
	};

	ShipParams newParams = {
		DEFAULT_PLAYER_SHIP_SPRITE_PARAMS,
		ROCKET,
		shipRect,
		SHIP_A_VELOCITY,
	};

	return newParams;
}