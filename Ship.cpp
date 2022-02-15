#include <iostream>
#include <vector>
#include "Ship.h"

const int FRAMES_PER_SHIP_UDPATE = 3;

Ship::Ship(
    SDL_Renderer* p_renderer,
    int p_screenWidth, 
    int p_screenHeight, 
    std::string path,
    SpriteParams shipParams
): Texture(p_renderer)
{
    x = (p_screenWidth - WIDTH) / 2;
    y = p_screenHeight - HEIGHT - 20;
    velX = velY = 0;
    frame = 0;
    screenWidth = p_screenWidth;
    screenHeight = p_screenHeight;

    loadFromSprite(path, shipParams);
}

void Ship::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w: 
            velY -= MAX_VELOCITY; break;
        case SDLK_DOWN: 
        case SDLK_s:
            velY += MAX_VELOCITY; break;
        case SDLK_LEFT:
        case SDLK_a:
            velX -= MAX_VELOCITY; break;
        case SDLK_RIGHT: 
        case SDLK_d:
            velX += MAX_VELOCITY; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP: 
            case SDLK_w:
                velY += MAX_VELOCITY; break;
            case SDLK_DOWN: 
            case SDLK_s:
                velY -= MAX_VELOCITY; break;
            case SDLK_LEFT: 
            case SDLK_a:
                velX += MAX_VELOCITY; break;
            case SDLK_RIGHT: 
            case SDLK_d:
                velX -= MAX_VELOCITY; break;
        }
    }
}

void Ship::move()
{
    x += velX;

    if ((x < 0) || (x + WIDTH > screenWidth))
    {
        x -= velX;
    }

    y += velY;

    if ((y < 0) || (y + HEIGHT > screenHeight))
    {
        y -= velY;
    }
}

int Ship::getPosX()
{
    return x;
}

int Ship::getPosY()
{
    return y;
}

void Ship::onBeforeRender()
{
    move();
    std::vector<SDL_Rect>& shipClips = getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
    render(getPosX(), getPosY(), currentClip);
}

void Ship::onAfterRender()
{
    ++frame;
    if (frame / FRAMES_PER_SHIP_UDPATE >= getClips().size())
    {
    	frame = 0;
    }
}