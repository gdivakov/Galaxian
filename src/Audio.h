#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <iostream>

#include "Object.h"

class Audio : public Object
{
public: 
	Audio();
	~Audio();
	bool loadMusic(std::string path);
	short loadSound(std::string path);
	void playMusic();
	void playSound(short key);
	void setMuted(bool isMuted, bool isMusic = true);
	virtual void handleEvent(SDL_Event& e);
	bool isMusicMuted;
	bool isSoundsMuted;
private:
	typedef std::map<short, Mix_Chunk*> SoundMap;
	short key;
	Mix_Music* mainTheme;
	SoundMap sounds;
};