#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "Loop.h"
#include "Object.h"
#include "Audio.h"

class Level {
public: 
	Level(SDL_Renderer* p_renderer);
	~Level();
	bool start();
	friend void onBeforeRender(Level* level);
	friend void onAfterRender(Level* level);
private:
	Loop gameLoop;
	Audio audioPlayer;
	SDL_Renderer* renderer;
	std::vector<Object*> objects;
};