#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Timer.h"
#include "LevelBase.h"

class MilesView : public Texture
{
public: 
	MilesView(LevelBase* p_level);
	~MilesView();
	void handleRender();
	void handlePaused();
	void handleResumed();
private:
	TTF_Font* font;
	Timer* timer;
	int milesPassed;
	LevelBase* level;
};

