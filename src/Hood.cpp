#include <iostream>

#include "SoundConst.h"
#include "Hood.h"
#include "StateView.h"

Hood::Hood(LevelBase* p_level)
{
    level = p_level;
    system = level->getSystem();
	renderer = system->getRenderer();

    pauseView = new PauseView(level, this);
    milesView = new MilesView(level);
    stateView = new StateView(level);
    // selectedWeaponView = new WeaponView(level);
    // armourView = new ArmourView(level);
    // buffsView = new BuffsView(level);
}

Hood::~Hood()
{
    delete pauseView;
    pauseView = NULL;
    renderer = NULL;
    level = NULL;
    system = NULL;
}

void Hood::handleEvent(SDL_Event& e)
{
    if (e.type != SDL_KEYDOWN)
    {
        return;
    }

    if (e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0 && !pauseView->isSettingsOpened)
    {
        return level->isPaused ? handleResumed() : handlePaused();
    }

    if (level->isPaused)
    {
        pauseView->handleEvent(e);
        return;
    }
}

void Hood::onBeforeRender()
{
    milesView->handleRender();
    stateView->handleRender();
}

void Hood::handlePaused()
{
    // Pause game and open pauseView
    Loop* gameLoop = system->getGameLoop();
    bool isPaused = level->togglePaused();
    Audio* audioPlayer = system->getAudioPlayer();

    audioPlayer->togglePaused(isPaused);
    audioPlayer->playSound(PAUSE_SOUND);

    milesView->handlePaused();

    // Render above all other objects
    gameLoop->addRenderListener(pauseView);
}

void Hood::handleResumed()
{
    Loop* gameLoop = system->getGameLoop();
    bool isPaused = level->togglePaused();
    Audio* audioPlayer = system->getAudioPlayer();

    audioPlayer->togglePaused(isPaused);
    audioPlayer->playSound(PAUSE_SOUND);

    milesView->handleResumed();

    gameLoop->removeRenderListener(pauseView);
}
