#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "App.h"
#include "SettingsConsts.h"

const int SOUND_FREQUENCY = 44100;
const char* APP_NAME = "Galaxian";

App::App(int screenWidth, int screenHeight)
{
	using std::cout;
	using std::endl;
	using std::string;

	std::vector<int> settingsConfig = readSettingsConfig();

	window = NULL;
	renderer = NULL;
	gameLoop = NULL;
	audioPlayer = NULL;

	status = true;
	windowed = !settingsConfig[FULLSCREEN_IDX];

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

	window = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

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

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		status = false;
		errMessage = "SDL_image could not initialize! SDL_image Error: " + string(IMG_GetError());
		return;
	}

	if (TTF_Init() == -1)
	{
		status = false;
		errMessage = "SDL_ttf could not initialize! SDL_ttf Error: " + string(TTF_GetError());
		return;
	}

	if (Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		status = false;
		errMessage = "SDL_mixer could not initialize! SDL_mixer Error: " + string(Mix_GetError());
		return;
	}

	gameLoop = new Loop(renderer);

	if (gameLoop == NULL)
	{
		status = false;
		errMessage = "Game loop could not initialize!";
		return;
	}

	audioPlayer = new Audio();

	if (audioPlayer == NULL)
	{
		status = false;
		errMessage = "Audio player could not initialize!";
		return;
	}

	//audioPlayer->setMuted(!settingsConfig[MUSIC_IDX]);
	//audioPlayer->setMuted(!settingsConfig[SOUNDS_IDX], false);

	windowSize = { screenWidth, screenHeight };

	//SDL_SetRelativeMouseMode(SDL_TRUE);

	if (!windowed)
	{
		enableFullScreen();
	}
}

App::~App()
{
	delete audioPlayer;
	delete gameLoop;

	audioPlayer = NULL;
	gameLoop = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

SDL_Renderer* App::getRenderer() const
{
	return renderer;
}

const SDL_Window* App::getWindow() const 
{
	return window;
}

Loop* App::getGameLoop() const
{
	return gameLoop;
}

Audio* App::getAudioPlayer() const
{
	return audioPlayer;
}

void App::enableFullScreen()
{
	int i = SDL_GetWindowDisplayIndex(window);
	SDL_Rect j;
	SDL_GetDisplayBounds(i, &j);
	windowSize.w = j.w;
	windowSize.h = j.h;
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void App::toggleWindowed()
{
	windowed = !windowed;

	if (windowed)
	{
		int i = SDL_GetWindowDisplayIndex(window);
		windowSize.w = WINDOWED_WIDTH;
		windowSize.w = WINDOWED_HEIGHT;
		SDL_SetWindowFullscreen(window, 0);
	}
	else
	{
		enableFullScreen();
	}
	//recalculateResolution(); //This function sets appropriate font sizes/UI positions
}

const Size* App::getWindowSize() const
{
	return &windowSize;
}

bool App::getStatus() const
{
	return status;
}

std::string App::getErrMessage() const
{
	return errMessage;
}