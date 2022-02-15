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
	//for (int i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->free();
	//}
}

bool Level::start()
{
	SpriteParams shipParams = { 109, 96, 3 };

	Background backgroundLvl1(renderer, "res/space.png");
	Ship playerShip(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "res/shipA.png", shipParams);

	bool res = audioPlayer.load("res/lvl1.mp3");
	audioPlayer.play();

	std::cout << res << std::endl;

	objects.push_back(&backgroundLvl1);
	objects.push_back(&playerShip);

	gameLoop.addListeners(objects);
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