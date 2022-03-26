#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "Level.h"

class Level1 : public Level {
public: 
	Level1(const App* p_system) : Level(p_system) {};
	virtual void start();
};