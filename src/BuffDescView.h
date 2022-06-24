#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "LevelBase.h"

class BuffDescView
{
public:
	BuffDescView(LevelBase* p_level, bool& p_isActive);
	~BuffDescView();

	void handleRender();
	void handleEvent(SDL_Event& e);
private:
	LevelBase* level;
	bool& isActive;
};

