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

bool Level::start()
{
	SpriteParams shipParams = { 109, 96, 3 }; // Todo: Move to const

	Background backgroundLvl1(renderer, "res/space.png");
	Ship playerShip(renderer, "res/shipA.png", shipParams);

	bool res = audioPlayer.load("res/lvl1.mp3");
	audioPlayer.play();

	std::cout << res << std::endl;

	objects.push_back(&backgroundLvl1);
	objects.push_back(&playerShip);

	gameLoop.addEventListeners(objects); // All objects are listening by default
	gameLoop.start(onBeforeRender, onAfterRender, this);

	playerShip.free();
	backgroundLvl1.free();

	return true;
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