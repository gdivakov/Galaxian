#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;

    isPaused = false;
    isStarted = false;
}

void Timer::start()
{
    isStarted = true;
    isPaused = false;

    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
    isStarted = false;
    isPaused = false;

    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause()
{
    if (isStarted && !isPaused)
    {
        isPaused = true;

        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if (isStarted && isPaused)
    {
        isPaused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    Uint32 time = 0;

    if (isStarted)
    {
        if (isPaused)
        {
            time = pausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool Timer::getIsStarted()
{
    return isStarted;
}

bool Timer::getIsPaused()
{
    return isPaused && isStarted;
}