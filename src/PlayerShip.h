#pragma once

#include <iostream>

#include "Ship.h"

class PlayerShip : public Ship
{
public:
    PlayerShip(const App* p_system, std::string path, ShipParams params);
    virtual void handleEvent(SDL_Event& e);
};