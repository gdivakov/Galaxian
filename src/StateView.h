#pragma once

#include <SDL.h>

#include "LevelBase.h"
#include "Texture.h"

class StateView
{
public:
	StateView(LevelBase* p_level);
	~StateView();
	void handleRender();
private:
	Texture* health;
	Texture* armor;
	LevelBase* level;
};

