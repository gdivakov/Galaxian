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
        LevelBase* p_level,
        ShipType type
    );

    int getMilesPassed();
    virtual void handleEvent(SDL_Event& e);
    virtual void onBeforeRender();
    virtual void startAccelerate();
protected:
    virtual void accelerate();
private:
    Uint32 acceleratedAt;
    int acceleratedMiles;
    bool startedMoving;
};