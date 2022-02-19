#pragma once
#include <SDL.h>
#include "Object.h"
#include "Texture.h"
#include "Consts.h"
#include "WeaponModule.h"
#include "App.h"

class Ship: public Texture
{
public:
    Ship(const App* system, std::string path, ShipParams params ); //Todo: remove renderer passing?
    void move();
    virtual void onBeforeRender();
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e);
private:
    int maxVelocity;
    SDL_Rect rect;
    int velX, velY;
    int frame;
    const App* system;
    WeaponModule gun;
};