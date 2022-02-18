#include <iostream>
#include <vector>
#include "Ship.h"

Ship::Ship(
    App* p_system,
    std::string path,
    ShipParams params
) : width(params.sprite.imageW),
    height(params.sprite.imageH),
    position({ (p_system->getWindowSize()->w - width) / 2, p_system->getWindowSize()->h - height - 20}), // Todo: Replace by function getPosition
    Texture(p_system->getRenderer()),
    gun(params.gunType, p_system->getRenderer(), &position)
{
    velX = velY = 0;
    frame = 0;

    loadFromSprite(path, params.sprite);

    system = p_system;
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
    gun.handleEvent(e);

}

void Ship::move()
{
    position.x += velX;

    if ((position.x < 0) || (position.x + width > system->getWindowSize()->w))
    {
        position.x -= velX;
    }

    position.y += velY;

    if ((position.y < 0) || (position.y + height > system->getWindowSize()->h))
    {
        position.y -= velY;
    }
}

void Ship::onBeforeRender()
{
    move();
    std::vector<SDL_Rect>& shipClips = getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
    render(position.x, position.y, currentClip);

    gun.onBeforeRender();
}

void Ship::onAfterRender()
{
    gun.onAfterRender();

    ++frame;
    if (frame / DEFAULT_PLAYER_SHIP_SPRITE_PARAMS.length >= getClips().size())
    {
    	frame = 0;
    }
}