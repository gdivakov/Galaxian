#pragma once
#include <iostream>

#include "LevelBase.h"
#include "Ship.h"
#include "ShipConsts.h"
#include "Consts.h"

class PlayerShip : public Ship
{
public:
    PlayerShip(
        const App* p_system, 
        LevelBase* p_level, 
        ShipType type
    );
    ~PlayerShip() {};
    virtual void handleEvent(SDL_Event& e);
    virtual void onBeforeRender();
};