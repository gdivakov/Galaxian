#pragma once
#include <SDL.h>
#include "Object.h"
#include "Texture.h"
#include "Consts.h"
#include "WeaponModule.h"

class Ship: public Texture
{
public:
    const int WIDTH = 109; // Todo: init from params
    const int HEIGHT = 102;
    const int MAX_VELOCITY = 5;

    Ship(SDL_Renderer* p_renderer, std::string path, SpriteParams shipParams ); //Todo: remove renderer passing?
    void move();
    virtual void onBeforeRender();
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e);
private:
    SDL_Point position;
    int velX, velY;
    int frame;
    WeaponModule gun;
};