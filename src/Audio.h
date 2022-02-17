#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

#include "Object.h"

class Audio : public Object
{
public: 
	Audio();
	~Audio();
	bool load(std::string path);
	void play();

	virtual void handleEvent(SDL_Event& e);
private: 
	Mix_Music* mainTheme;
};