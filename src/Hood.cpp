#include "Hood.h"
#include <iostream>

Hood::Hood(SDL_Renderer* p_renderer, LevelBase* p_level, const App* p_system)
{
	renderer = p_renderer;
    level = p_level;
    system = p_system;
    pauseView = new PauseView(system, p_level);
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

    if (e.key.keysym.sym == SDLK_ESCAPE && !pauseView->isSettingsOpened)
    {
        // Pause game and open pauseView
        bool isPaused = level->togglePaused();
        system->getAudioPlayer()->togglePaused(isPaused);
        return;
    }

    if (level->isPaused)
    {
        pauseView->handleEvent(e);
        return;
    }
}

void Hood::onBeforeRender()
{
    if (level->isPaused)
    {
        pauseView->handleRender();
    }
}
