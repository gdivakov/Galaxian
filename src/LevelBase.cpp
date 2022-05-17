#include "LevelBase.h"

Ship* LevelBase::getPlayer()
{
	return spawner ? spawner->getPlayer() : NULL;
}

void LevelBase::unload()
{
	deregisterListeners();

	for (int i = 0; i < objsToFree.size(); i++)
	{
		delete objsToFree[i];
	}

	system->getAudioPlayer()->freeSounds();
	system->getAudioPlayer()->freeMusic();

	spawner = NULL;
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

void LevelBase::quit()
{
	controller->stop();
}

bool LevelBase::togglePaused()
{
	isPaused = !isPaused;

	// Pause/Unpause system timer
	if (isPaused)
	{
		system->getTimer()->pause();
	}
	else 
	{
		system->getTimer()->unpause();
	}

	return isPaused;
}