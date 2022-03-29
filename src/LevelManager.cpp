#include "LevelManager.h"
#include "MainScreen.h"
#include "Level1.h"
//#include "Settings.h"

LevelManager::LevelManager(const App* p_system) : system(p_system)
{
	activeLevelIdx = MAIN_MENU;

	//isPaused = false;
	
	levels = {
		new MainScreen(system, this),
		new Level1(system, this),
		//new Settings(system, this)
	};
}

// Stop loop, unload prev level, load next level, start loop
void LevelManager::start(LEVELS nextLevelIdx)
{
	//if (!isPaused)
	//{
		stop();
	//}

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

//// Pause means stop handling events from screen but still render it
//void LevelManager::pause()
//{
//	if (isPaused)
//	{
//		return throw("LevelManager Error: Only one level could be paused in current implementation!");
//	}
//
//	Loop* gameLoop = system->getGameLoop();
//	gameLoop->stop();
//
//	levels[activeLevelIdx]->deregisterListeners();
//	isPaused = true;
//}

LevelManager::~LevelManager()
{
	for (int i = 0; i < levels.size(); i++)
	{
		delete levels[i];
	}
}