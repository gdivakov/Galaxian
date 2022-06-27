#include "LevelBase.h"

LevelBase::LevelBase(const App* p_system, LevelManager* p_controller) :
	system(p_system),
	renderer(system->getRenderer()),
	controller(p_controller),
	isPaused(false) 
{
	timer = new Timer();
	//initAudio();
};

LevelBase::~LevelBase()
{
	unload();

	system->getAudioPlayer()->freeSounds();
	system->getAudioPlayer()->freeMusic();

	delete timer;
}

void LevelBase::accelerate()
{
	isAccelerated = true;
	acceleratedAt = getTime();

	spawner->accelerate();
}

void LevelBase::stopAcceleration()
{ 
	isAccelerated = false; 
	spawner->stopAcceleration();
};

void LevelBase::restart() { 
	unload(); 
	load(); 
	nextEnemyIdx = 0; 
};

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

Ship* LevelBase::getPlayer() { return spawner ? spawner->getPlayer() : NULL; };

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
		timer->pause();
	}
	else 
	{
		timer->unpause();
	}

	return isPaused;
}