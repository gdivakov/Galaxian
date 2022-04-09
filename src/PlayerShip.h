#pragma once

#include <iostream>

#include "Ship.h"

class PlayerShip : public Ship
{
public:
    PlayerShip(
        const App* p_system, 
        LevelBase* p_level, 
        ShipParams params
    );
    virtual void handleEvent(SDL_Event& e);
    virtual void onBeforeRender();
    void handleCollided();
};