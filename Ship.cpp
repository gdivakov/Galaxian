#include <iostream>
#include <vector>
#include "Ship.h"

const int FRAMES_PER_SHIP_UDPATE = 3;

Ship::Ship(
    SDL_Renderer* p_renderer,
    std::string path,
    SpriteParams shipParams
) : position({ (SCREEN_WIDTH - WIDTH) / 2, SCREEN_HEIGHT - HEIGHT - 20 }), // Todo: Replace by function getPosition
    Texture(p_renderer), 
    gun(ROCKET, p_renderer, &position) // Todo: type should come from above
{
    velX = velY = 0;
    frame = 0;

    loadFromSprite(path, shipParams);
}

void Ship::handleEvent(SDL_Event& e)
{
    gun.handleEvent(e);

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
    position.x += velX;

    if ((position.x < 0) || (position.x + WIDTH > SCREEN_WIDTH))
    {
        position.x -= velX;
    }

    position.y += velY;

    if ((position.y < 0) || (position.y + HEIGHT > SCREEN_HEIGHT))
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
    ++frame;
    if (frame / FRAMES_PER_SHIP_UDPATE >= getClips().size())
    {
    	frame = 0;
    }
}