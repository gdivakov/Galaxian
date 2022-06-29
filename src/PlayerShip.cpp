#include "PlayerShip.h"
#include "SpecialsConsts.h"

PlayerShip::PlayerShip(
    LevelBase* p_level,
    ShipType type) 
    :
    Ship(p_level->getSystem(), SHIP_PARAMS.at(type), p_level, false)
{
    rotation = 0;
    pos = Vector2((WINDOWED_WIDTH)/2, WINDOWED_HEIGHT - getTexture()->getHeight() - 20);
    isMoveStarted = false;
    isRotatingLeft = false;
    isRotatingRight = false;
    hasReachedEnd = false;
    acceleratedMiles = 0;
}

void PlayerShip::handleEvent(SDL_Event& e)
{
    // Gun events
    if (!isActive)
    {
        gun->setIsShooting(false);
    }

    bool isNotRepeat = e.key.repeat == 0;

    if (e.type == SDL_KEYDOWN && !level->getIsCompleted())
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_l:
            gun->setIsShooting(true);
            return;
        case SDLK_f:
            if (!isNotRepeat || !isActive || level->isPaused)
            {
                break;
            }

            gun->selectNextGun();
        }
    }

    if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_l:
            gun->setIsShooting(false);
            return;
        }
    }

    // Ship events
    if (level->isPaused || hasReachedEnd || !specials.status->getHealth())
    {
        return;
    }

    if (e.type == SDL_KEYDOWN && isNotRepeat)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_e:
            isRotatingLeft = false;
            isRotatingRight = true;
            break;
        case SDLK_q:
            isRotatingLeft = true;
            isRotatingRight = false;
        }
    }

    if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_e:
            isRotatingRight = false;
        case SDLK_q:
            isRotatingLeft = false;
        }
    }

    if (e.type == SDL_KEYDOWN && isNotRepeat)
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
    
    if (e.type == SDL_KEYUP && isNotRepeat && isMoveStarted)
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
}

void PlayerShip::onBeforeRender()
{
    if (!level->isPaused && !hasReachedEnd)
    {
        level->getIsCompleted() ? moveToFinish() : move();
    }

    // handle rotation
    if (isRotatingLeft)
    {
        rotate(rotation - 4);
    }
    
    if (isRotatingRight)
    {
        rotate(rotation + 4);
    }

    std::cout << isRotatingRight << ":" << isRotatingLeft << std::endl;

    gun->handleRender();
    specials.buff->updateBuffs();

    std::vector<SDL_Rect>& shipClips = getTexture()->getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

    Size& size = getTexture()->size;

    getTexture()->render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
}

void PlayerShip::moveToFinish()
{
    if (pos.y + getTexture()->size.h < 0)
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
