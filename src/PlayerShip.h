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
    virtual void startAcceleration() {};
protected:
    virtual void handleAcceleration();
private:
    int acceleratedMiles;
    bool isMoveStarted;
    bool hasReachedEnd = false;

    void moveToFinish();
};