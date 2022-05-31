#include "LevelBase.h"

Ship* LevelBase::getPlayer()
{
	return spawner ? spawner->getPlayer() : NULL;
}

LevelBase::~LevelBase()
{
	unload();

	system->getAudioPlayer()->freeSounds();
	system->getAudioPlayer()->freeMusic();
}

void LevelBase::unload()
{
	deregisterListeners();

	for (int i = 0; i < objsToFree.size(); i++)
	{
		delete objsToFree[i];
	}

	objsToFree.clear();

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

	eventListeners.clear();
	renderListeners.clear();

	gameLoop->removeEventListeners();
	gameLoop->removeRenderListeners();
}

void LevelBase::quit()
{
	controller->stop();
	system->getGameLoop()->stop();
}

bool LevelBase::togglePaused()
{
	isPaused = !isPaused;

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