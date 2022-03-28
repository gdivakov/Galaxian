#include "LevelBase.h"

void LevelBase::unload()
{
	deregisterListeners();

	for (int i = 0; i < objsToFree.size(); i++)
	{
		delete objsToFree[i];
	}
}

void LevelBase::registerListeners()
{
	Loop* gameLoop = system->getGameLoop();

	gameLoop->addEventListeners(eventListeners);
	gameLoop->addRenderListeners(renderListeners);
}

void LevelBase::deregisterListeners()
{
	Loop* gameLoop = system->getGameLoop();

	gameLoop->removeEventListeners(eventListeners);
	gameLoop->removeRenderListeners(renderListeners);

	objsToFree.clear();
}