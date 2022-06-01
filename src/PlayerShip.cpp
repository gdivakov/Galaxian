#include "PlayerShip.h"
#include "ShipSpecialsConsts.h"

PlayerShip::PlayerShip(
    LevelBase* p_level,
    ShipType type) 
    :
    Ship(p_level->getSystem(), getShipParams(type), p_level, false)
{
    rotation = 0;
    acceleratedAt = 0;
    pos = Vector2((WINDOWED_WIDTH)/2, WINDOWED_HEIGHT - getHeight() - 20);
}

void PlayerShip::handleEvent(SDL_Event& e)
{
    if (level->isPaused || !specials.status->getHealth())
    {
        return;
    }

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_e:
            rotate(rotation + 10); break;
        case SDLK_q:
            rotate(rotation - 10); break;
        }
    }

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            vel.y -= maxSpeed; break;
        case SDLK_DOWN:
        case SDLK_s:
            vel.y += maxSpeed; break;
        case SDLK_LEFT:
        case SDLK_a:
            vel.x -= maxSpeed; break;
        case SDLK_RIGHT:
        case SDLK_d:
            vel.x += maxSpeed; break;
        }
    }
    else if (
        e.type == SDL_KEYUP && 
        e.key.repeat == 0)    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_w:
            vel.y += maxSpeed; break;
        case SDLK_DOWN:
        case SDLK_s:
            vel.y -= maxSpeed; break;
        case SDLK_LEFT:
        case SDLK_a:
            vel.x += maxSpeed; break;
        case SDLK_RIGHT:
        case SDLK_d:
            vel.x -= maxSpeed; break;
        }
    }

    gun->handleEvent(e);
}

void PlayerShip::onBeforeRender()
{
    if (!level->isPaused)
    {
        move();
    }

    gun->onBeforeRender();
    specials.buff->updateBuffs();

    std::vector<SDL_Rect>& shipClips = getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

    //showColliders();
    render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
}

void PlayerShip::startAccelerate()
{
    isAccelerated = true;

    acceleratedAt = level->getSystem()->getTimer()->getTicks();
}

void PlayerShip::accelerate()
{
    if (!isAccelerated)
    {
        return;
    }

    Uint32 time = level->getSystem()->getTimer()->getTicks();

    acceleratedMiles = (time - acceleratedAt) * ACCELERATION_SPEED_MP;

    BuffParams speedUpPararms = getBuffParamsByType(BUFF_SPEED_UP);
    bool isAccelerationFinished = acceleratedAt + speedUpPararms.duration < time;

    if (isAccelerationFinished)
    {
        acceleratedAt = 0;
        isAccelerated = false;
    }
}

int PlayerShip::getMilesPassed() 
{ 
    return level->getSystem()->getTimer()->getTicks() + acceleratedMiles; 
};
