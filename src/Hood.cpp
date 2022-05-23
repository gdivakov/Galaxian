#include <iostream>

#include "SoundConst.h"
#include "Hood.h"
#include "StatusBarView.h"
#include "BuffBarView.h"

Hood::Hood(LevelBase* p_level)
{
    level = p_level;
    system = level->getSystem();
	renderer = system->getRenderer();

    pauseView = new PauseView(level, this);
    milesView = new MilesView(level);
    statusView = new StatusBarView(level);
    buffView = new BuffBarView(level);
    gameOverView = new GameOverView(level);

    // selectedWeaponView = new WeaponView(level);
}

Hood::~Hood()
{
    delete pauseView;
    delete milesView;
    delete statusView;
    delete buffView;
    delete gameOverView;

    pauseView = NULL;
    milesView = NULL;
    statusView = NULL;
    buffView = NULL;
    gameOverView = NULL;

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

    if (gameOverView->getIsActive())
    {
        return gameOverView->handleEvent(e);
    }

    if (e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0 && !pauseView->isSettingsOpened)
    {
        return level->isPaused ? handleResumed() : handlePaused();
    }

    if (level->isPaused)
    {
        return pauseView->handleEvent(e);
    }
}

void Hood::onBeforeRender()
{
    if (!level->getPlayer() && !gameOverView->getIsActive()) // Player is dead
    {
        gameOverView->setIsActive(true);
    }

    milesView->handleRender();
    statusView->handleRender();
    buffView->handleRender();
    gameOverView->handleRender();
}

void Hood::handlePaused()
{
    // Pause game and open pauseView
    Loop* gameLoop = system->getGameLoop();
    bool isPaused = level->togglePaused();
    Audio* audioPlayer = system->getAudioPlayer();

    audioPlayer->togglePaused(isPaused);
    audioPlayer->playSound(PAUSE_SOUND);

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

    gameLoop->removeRenderListener(pauseView);
}
