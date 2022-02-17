#include <iostream>
#include <SDL.h>

#include "Level.h"
#include "Ship.h"
#include "Loop.h"
#include "Background.h"
#include "Consts.h"

void onBeforeRender(Level* level);
void onAfterRender(Level* level);

Level::Level(SDL_Renderer* p_renderer): gameLoop(p_renderer)
{
	renderer = p_renderer;
}

Level::~Level()
{
	renderer = NULL;
}

void Level::start()
{
	Background backgroundLvl1(renderer, "res/space.png");
	Ship playerShip(renderer, "res/shipA.png", DEFAULT_PLAYER_SHIP_SPRITE_PARAMS);

	audioPlayer.load("res/lvl1.mp3");
	//audioPlayer.play(); 

	objects.push_back(&backgroundLvl1);
	objects.push_back(&playerShip);

	// All level objects are listening by default
	gameLoop.addEventListeners(objects); 
	gameLoop.start(onBeforeRender, onAfterRender, this);
}

void onBeforeRender(Level* level)
{
	for (int i = 0; i < level->objects.size(); i++)
	{
		level->objects[i]->onBeforeRender();
	}
}

void onAfterRender(Level* level)
{
	for (int i = 0; i < level->objects.size(); i++)
	{
		level->objects[i]->onAfterRender();
	}
}