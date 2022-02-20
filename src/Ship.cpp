#include <iostream>
#include <vector>
#include "Ship.h"

Ship::Ship(
    const App* p_system,
    std::string path,
    ShipParams params
) : rect(params.rect),
    system(p_system),
    Texture(p_system->getRenderer()),
    gun(params.gunType, p_system->getRenderer(), this),
    type(params.type)
{
    frame = 0;
    velX = velY = 0;
    maxVelocity = params.maxVelocity;

    loadFromSprite(path, params.sprite);
}

SDL_Rect* Ship::getRect()
{
    return &rect;
}

void Ship::handleEvent(SDL_Event& e)
{
    if (type != SONIC_A)
    {
        // Controlling programmatically
        return;
    }

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            velY -= maxVelocity; break;
        case SDLK_DOWN:
        case SDLK_s:
            velY += maxVelocity; break;
        case SDLK_LEFT:
        case SDLK_a:
            velX -= maxVelocity; break;
        case SDLK_RIGHT:
        case SDLK_d:
            velX += maxVelocity; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP: 
            case SDLK_w:
                velY += maxVelocity; break;
            case SDLK_DOWN: 
            case SDLK_s:
                velY -= maxVelocity; break;
            case SDLK_LEFT: 
            case SDLK_a:
                velX += maxVelocity; break;
            case SDLK_RIGHT: 
            case SDLK_d:
                velX -= maxVelocity; break;
        }
    }
    gun.handleEvent(e);

}

void Ship::move()
{
    rect.x += velX;

    if ((rect.x < 0) || (rect.x + rect.w > system->getWindowSize()->w))
    {
        rect.x -= velX;
    }

    rect.y += velY;

    if ((rect.y < 0) || (rect.y + rect.h > system->getWindowSize()->h))
    {
        rect.y -= velY;
    }
}

void Ship::onBeforeRender()
{
    move();
    std::vector<SDL_Rect>& shipClips = getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
    render(rect.x, rect.y, currentClip);

    gun.onBeforeRender();
}

void Ship::onAfterRender()
{
    gun.onAfterRender();
    
    int clipLength = getClips().size();

    ++frame;
    if (frame / clipLength >= clipLength)
    {
    	frame = 0;
    }
}