#pragma once
#include <SDL.h>

#include "Texture.h"
#include "App.h"
#include "LevelBase.h"

class DynamicBackground : public Texture
{
private:
	int scrollingOffset;
	LevelBase* level;
public:
	DynamicBackground(SDL_Renderer* p_renderer, std::string path, LevelBase* p_level);
	virtual void onBeforeRender();
	virtual void handleEvent(SDL_Event& e) {};
};