#pragma once

#include <SDL.h>

#include "LevelBase.h"
#include "Texture.h"

class StatusBarView
{
public:
	StatusBarView(LevelBase* p_level);
	~StatusBarView();
	void handleRender();
private:
	Texture* health;
	Texture* armor;
	LevelBase* level;
};

