#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

#include "Audio.h"
#include "Loop.h"
#include "Consts.h"
#include "Timer.h"

class App
{
public: 
	App(int screenWidth, int screenHeight);
	~App();
	void toggleWindowed();
	bool getStatus() const;
	std::string getErrMessage() const;
	SDL_Renderer* getRenderer() const;
	Loop* getGameLoop() const;
	Audio* getAudioPlayer() const;
	const SDL_Window* getWindow() const;
	const Size* getWindowSize() const;
	void enableFullScreen();
	Timer* getTimer() const { return timer; };
private: 
	Loop* gameLoop;
	Audio* audioPlayer;
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool status;
	std::string errMessage;
	bool windowed;
	Size windowSize;
	Timer* timer;
};