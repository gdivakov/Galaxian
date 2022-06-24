#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <iostream>

class Audio
{
public: 
	Audio();
	~Audio();
	bool loadMusic(std::string path);
	bool loadSound(std::string path);
	void playMusic();
	void playSound(std::string key);
	void setMuted(bool isMuted, bool isMusic = true);
	void togglePaused(bool p_isPaused = false);
	bool isMusicMuted;
	bool isSoundsMuted;
	void freeSounds();
	void stopSounds();
	void stopMusic();
	void freeMusic();
private:
	typedef std::map<std::string, Mix_Chunk*> SoundMap;
	Mix_Music* mainTheme;
	SoundMap sounds;
	bool isPaused;
};