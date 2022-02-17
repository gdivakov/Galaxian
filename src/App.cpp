#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "App.h"

const int SOUND_FREQUENCY = 44100;

App::App(int screenWidth, int screenHeight)
{
	using std::cout;
	using std::endl;
	using std::string;

	window = NULL;
	renderer = NULL;
	status = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		status = false;
		errMessage = "SDL could not initialize! SDL Error: " + string(SDL_GetError());

		return;
	}

	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		cout << "Warning: Linear texture filtering not enabled!" << endl;
	}

	window = SDL_CreateWindow("Galaxian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		status = false;
		errMessage = "Window could not be created! SDL Error: " + string(SDL_GetError());

		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
	{
		status = false;
		errMessage = "Renderer could not be created! SDL Error: " + string(SDL_GetError());

		return;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		status = false;
		errMessage = "SDL_image could not initialize! SDL_image Error: " + string(IMG_GetError());

		return;
	}

	if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		status = false;
		errMessage = "SDL_mixer could not initialize! SDL_mixer Error: " + string(Mix_GetError());
		return;
	}
}

App::~App()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* App::getRenderer()
{
	return renderer;
}

SDL_Window* App::getWindow()
{
	return window;
}

bool App::getStatus()
{
	return status;
}

std::string App::getErrMessage()
{
	return errMessage;
}