#include "PlayerShip.h"

PlayerShip::PlayerShip(const App* p_system, std::string path, ShipParams params) : 
	Ship(p_system, path, params)
{
}

void PlayerShip::handleEvent(SDL_Event& e)
{
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