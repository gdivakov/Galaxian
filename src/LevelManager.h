#pragma once
#include <vector>

#include "App.h"
#include "LevelBase.h"

const enum LEVELS { MAIN_MENU, LEVEL_1 };

class LevelManager
{
public:
	LevelManager(const App* p_system);
	~LevelManager();
	void start(LEVELS nextLevel);
	void stop();
private:
	const App* system;
	LEVELS activeLevelIdx;
	std::vector<LevelBase*> levels;
};

