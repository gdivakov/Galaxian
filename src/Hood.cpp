#include <iostream>

#include "SoundConst.h"
#include "Hood.h"

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
    totalView = new TotalView(level);

    // selectedWeaponView = new WeaponView(level);
    // totals = new Totals(level);
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
    totalView = NULL;

    renderer = NULL;
    level = NULL;
    system = NULL;
}

void Hood::showTotal()
{
    totalView->setIsActive(true);
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

    if (e.key.keysym.sym == SDLK_ESCAPE && 
        e.key.repeat == 0 && 
        !pauseView->hasNestedActive() &&
        !level->getIsCompleted())
    {
        return level->isPaused ? handleResumed() : handlePaused();
    }

    if (level->isPaused)
    {
        return pauseView->handleEvent(e);
    }

    totalView->handleEvent(e);
}

void Hood::onBeforeRender()
{
    if (!level->getPlayer() && !gameOverView->getIsActive()) // Player is dead
    {
        gameOverView->setIsActive(true);
    }

    if (!totalView->getIsActive())
    {
        milesView->handleRender();
        statusView->handleRender();
        buffView->handleRender();
        gameOverView->handleRender();
    }

    totalView->handleRender();
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
