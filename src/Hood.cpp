#include <iostream>

#include "SoundConst.h"
#include "Hood.h"

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

    if (e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat == 0 && !pauseView->isSettingsOpened)
    {
        // Pause game and open pauseView
        bool isPaused = level->togglePaused();
        Audio* audioPlayer = system->getAudioPlayer();
        
        audioPlayer->togglePaused(isPaused);
        audioPlayer->playSound(PAUSE_SOUND);

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
