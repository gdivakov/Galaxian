#pragma once
#include <SDL.h>

class Timer
{
public: 
	Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    Uint32 getTicks();

    bool getIsStarted();
    bool getIsPaused();
private:
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool isPaused;
    bool isStarted;
};