#include "Audio.h"
#include "SettingsConsts.h"

const int MUSIC_VOLUME = MIX_MAX_VOLUME / 10;
const int SOUNDS_VOLUME = MIX_MAX_VOLUME / 20;

Audio::Audio()
{
	std::vector<int> settingsConfig = readSettingsConfig();

	isMusicMuted = !settingsConfig[MUSIC_IDX];
	isSoundsMuted = !settingsConfig[SOUNDS_IDX];

	mainTheme = NULL;
	isPaused = false;

	Mix_VolumeMusic(!isMusicMuted ? MUSIC_VOLUME : 0);
	Mix_Volume(-1, !isSoundsMuted ? SOUNDS_VOLUME : 0);
}

void Audio::freeSounds()
{
	for (SoundMap::iterator i = sounds.begin(); i != sounds.end(); i++)
	{
		Mix_FreeChunk(i->second);
	}

	sounds.clear();
}

void Audio::freeMusic()
{
	if (mainTheme)
	{
		Mix_FreeMusic(mainTheme);
		mainTheme = NULL;
	}
}

Audio::~Audio()
{
	freeSounds();
	freeMusic();
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

bool Audio::loadSound(std::string path)
{
	sounds[path] = Mix_LoadWAV(path.c_str());

	if (sounds[path] == NULL)
	{
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}

void Audio::playMusic()
{
	Mix_PlayMusic(mainTheme, -1);
}

void Audio::playSound(std::string key)
{
	if (!sounds[key])
	{
		std::cout << "Error while playing sound id: " << key << std::endl;
		std::cout << Mix_GetError() << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	Mix_PlayChannel(-1, sounds[key], 0);
};

void Audio::setMuted(bool isMuted, bool isMusic)
{
	if (isMusic)
	{
		isMusicMuted = isMuted;
		Mix_VolumeMusic(isMuted ? 0 : MUSIC_VOLUME);
	}
	else
	{
		isSoundsMuted = isMuted;
		Mix_Volume(-1, isMuted ? 0 : SOUNDS_VOLUME);
	}
}

void Audio::togglePaused(bool p_isPaused)
{
	isPaused = p_isPaused;

	if (isPaused)
	{
		Mix_PauseMusic();
	}
	else {
		Mix_ResumeMusic();
	}
}