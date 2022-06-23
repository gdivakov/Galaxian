#include "PlayerShip.h"
#include "ShipSpecialsConsts.h"

PlayerShip::PlayerShip(
    LevelBase* p_level,
    ShipType type) 
    :
    Ship(p_level->getSystem(), getShipParams(type), p_level, false)
{
    rotation = 0;
    pos = Vector2((WINDOWED_WIDTH)/2, WINDOWED_HEIGHT - getHeight() - 20);
}

void PlayerShip::handleEvent(SDL_Event& e)
{
    if (level->isPaused || hasReachedEnd || !specials.status->getHealth())
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
        if (!isMoveStarted)
        {
            isMoveStarted = true; // To prevent cases when level starts from keyUp event
        }

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
    
    if (e.type == SDL_KEYUP && e.key.repeat == 0 && isMoveStarted)
    {
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
    if (!level->isPaused && !hasReachedEnd)
    {
        level->getIsCompleted() ? moveToFinish() : move();
    }

    gun->onBeforeRender();
    specials.buff->updateBuffs();

    std::vector<SDL_Rect>& shipClips = getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

    render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
}

void PlayerShip::moveToFinish()
{
    if (pos.y + size.h < 0)
    {
        hasReachedEnd = true;
        level->handleCompleted();
        return;
    }

    rotation = 0;
    Vector2 velToAdd = Vector2(0, -3);
    pos += velToAdd;

    shiftColliders();
}

void PlayerShip::handleAcceleration()
{
    if (!level->getIsAccelerated())
    {
        return;
    }

    acceleratedMiles = (level->getTime() - level->getAcceleratedAt()) * ACCELERATION_SPEED_MP;
}

int PlayerShip::getMilesPassed() 
{ 
    return level->getTime() + acceleratedMiles; 
};
