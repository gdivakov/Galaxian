#pragma once
#include <SDL.h>

#include "Texture.h"
#include "App.h"
#include "LevelBase.h"

class Background : public Texture
{
public: 
	Background(SDL_Renderer* p_renderer, std::string path) : Texture(p_renderer) { loadFromFile(path); };
	virtual void onBeforeRender() { render(0, 0); return; };
	virtual void handleEvent() {};
};