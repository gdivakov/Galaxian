#pragma once
#include <SDL.h>
#include "Object.h"
#include "Texture.h"
#include "Consts.h"

class Ship: public Texture
{
public:
    static const int WIDTH = 98;
    static const int HEIGHT = 90;
    static const int MAX_VELOCITY = 5;

    Ship(
        SDL_Renderer* p_renderer, 
        int p_screenWidth, 
        int p_screenHeight, 
        std::string path, 
        SpriteParams shipParams
    );
    void move();
    int getPosX();
    int getPosY();
    virtual void onBeforeRender();
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e);
private:
    int x, y;
    int velX, velY;
    int screenWidth;
    int screenHeight;
    int frame;
};