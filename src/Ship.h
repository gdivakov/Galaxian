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
    const int MAX_VELOCITY = 5;

    Ship(App* system, std::string path, ShipParams params ); //Todo: remove renderer passing?
    void move();
    virtual void onBeforeRender();
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e);
private:
    int width, height;
    SDL_Point position;
    int velX, velY;
    int frame;
    App* system;
    WeaponModule gun;
};