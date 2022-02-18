#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

#include "Audio.h"
#include "Loop.h"

struct Size 
{
	int w;
	int h;
};

const int WINDOWED_WIDTH = 920;
const int WINDOWED_HEIGHT = 620;

class App // Todo: rename to system?
{
public: 
	App(int screenWidth, int screenHeight);
	~App();
	void toggleWindowed();

	bool getStatus();
	std::string getErrMessage();
	SDL_Renderer* getRenderer();
	Loop* getGameLoop();
	Audio* getAudioPlayer();
	SDL_Window* getWindow();
	Size* getWindowSize();
private: 
	Loop* gameLoop;
	Audio* audioPlayer; // Todo: move to App
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool status;
	std::string errMessage;
	bool windowed;
	Size windowSize;
};