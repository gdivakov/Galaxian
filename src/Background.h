#pragma once
#include <SDL.h>

#include "Texture.h"
#include "App.h"
#include "LevelBase.h"

class Background : public Texture
{
private:
	int scrollingOffset;
	bool isDynamic;
	LevelBase* level;
public: 
	Background(SDL_Renderer* p_renderer, std::string path, LevelBase* p_level, bool p_isDynamic = true);
	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent(SDL_Event& e);
};