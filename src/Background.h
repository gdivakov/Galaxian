#pragma once
#include <SDL.h>

#include "Texture.h"
#include "App.h"

class Background : public Texture
{
private:
	int scrollingOffset;
	bool isDynamic;
public: 
	Background(SDL_Renderer* p_renderer, std::string path, bool p_isDynamic = true);
	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent(SDL_Event& e);
};