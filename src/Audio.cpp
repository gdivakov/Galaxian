#include "Audio.h"

Audio::Audio()
{
	mainTheme = NULL;
	key = 1; // 0 is reserved for error case
}

Audio::~Audio()
{

	for (SoundMap::iterator i = sounds.begin(); i != sounds.end(); i++)
	{
		Mix_FreeChunk(i->second);
	}
	
	sounds.clear();

	Mix_FreeMusic(mainTheme);
	mainTheme = NULL;
}

bool Audio::loadMusic(std::string path)
{
	mainTheme = Mix_LoadMUS(path.c_str());

	if (mainTheme == NULL)
	{
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	return mainTheme != NULL;
}

short Audio::loadSound(std::string path) // Todo: set up correct volume level
{
	short id = key;
	key++;

	sounds[id] = Mix_LoadWAV(path.c_str());

	if (sounds[id] == NULL)
	{
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return 0;
	}

	return id;
}

void Audio::playMusic()
{
	Mix_PlayMusic(mainTheme, -1);
}

void Audio::playSound(short id)
{
	if (!sounds[id])
	{
		std::cout << "Error while playing sound id: " << id << std::endl;
		return;
	}

	Mix_PlayChannel(-1, sounds[id], 0);
};

void Audio::handleEvent(SDL_Event& e)
{}