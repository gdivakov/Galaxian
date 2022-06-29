#pragma once
#include <iostream>

#include "LevelBase.h"
#include "Ship.h"
#include "ShipConsts.h"

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
    void onAccelerate();
private:
    int acceleratedMiles;
    bool hasReachedEnd;
    bool isRotatingLeft;
    bool isRotatingRight;
    bool isMoveStarted;

    void moveToFinish();
    virtual void handleAcceleration();
};