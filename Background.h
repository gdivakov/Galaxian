#pragma once
#include <SDL.h>

#include "Texture.h"

class Background : public Texture
{
public: 
	Background(SDL_Renderer* p_renderer, std::string path);
	~Background();
	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent();
private:
	int scrollingOffset;
};