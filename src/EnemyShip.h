#pragma once

#include <iostream>

#include "PlayerShip.h"
#include "Vector2.h"
#include "Ship.h"

class EnemyShip : public Ship
{
    SDL_Rect* playerRect;
    int rotate;
    Vector2 dir;
public:
    EnemyShip(const App* p_system, std::string path, ShipParams params, PlayerShip& player);
    virtual void onBeforeRender();
    virtual void onAfterRender();
    void checkDirections();
    virtual void handleEvent(SDL_Event& e);
    ~EnemyShip();
};