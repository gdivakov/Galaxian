#include "LevelManager.h"
#include "MainScreen.h"
#include "Level1.h"

LevelManager::LevelManager(const App* p_system) : system(p_system)
{
	activeLevelIdx = MAIN_MENU;

	levels = {
		new MainScreen(system, this),
		new Level1(system, this)
	};
}

// Stop loop, unload prev level, load next level, start loop
void LevelManager::start(LEVELS nextLevelIdx)
{
	stop();

	LevelBase* nextLevel = levels[nextLevelIdx];
	nextLevel->load();

	activeLevelIdx = nextLevelIdx;

	Loop* gameLoop = system->getGameLoop();
	gameLoop->start();
}

void LevelManager::stop()
{
	Loop* gameLoop = system->getGameLoop();
	gameLoop->stop();

	levels[activeLevelIdx]->unload();
}

LevelManager::~LevelManager()
{
	for (int i = 0; i < levels.size(); i++)
	{
		delete levels[i];
	}
}