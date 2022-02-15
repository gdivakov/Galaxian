#include "Audio.h"

Audio::Audio()
{
	mainTheme = NULL;
}

Audio::~Audio()
{
	Mix_FreeMusic(mainTheme);
	mainTheme = NULL;
}

bool Audio::load(std::string path)
{
	mainTheme = Mix_LoadMUS(path.c_str());

	if (mainTheme == NULL)
	{
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	return mainTheme != NULL;
}

void Audio::play()
{
	Mix_PlayMusic(mainTheme, -1);
}

void Audio::handleEvent(SDL_Event& e)
{}