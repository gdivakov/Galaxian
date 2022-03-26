#pragma once
#include <SDL.h>

#include "Texture.h"
#include "App.h"

const enum Type { STATIC, DYNAMIC };

class Background : public Texture
{
private:
	int scrollingOffset;
	Type mode;
	const App* system;
public: 
	Background(SDL_Renderer* p_renderer, std::string path, Type p_mode = DYNAMIC, const App* p_system = NULL);
	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent(SDL_Event& e);
};