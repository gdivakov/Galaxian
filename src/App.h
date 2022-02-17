#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>

class App
{
public: 
	App(int screenWidth, int screenHeight);
	~App();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	bool getStatus();
	std::string getErrMessage();
private: 
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool status;
	std::string errMessage;
};