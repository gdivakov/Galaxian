#include "PlayerShip.h"
#include "ShipSpecialsConsts.h"

const Vector2 DEFAULT_GUN_POS = Vector2();
const Vector2 DIFFUSER_GUN_POS = Vector2(0, 25);
const Vector2 BLAST_DOUBLE_GUN_POS = Vector2(-10, 0);

PlayerShip::PlayerShip(
    LevelBase* p_level,
    ShipType type) 
    :
    Ship(p_level->getSystem(), getShipParams(type), p_level, false)
{
    rotation = 0;
    pos = Vector2((WINDOWED_WIDTH)/2, WINDOWED_HEIGHT - getTexture()->getHeight() - 20);
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

            GunType selectedGun = gun->selectNextGun();

            gun->setGunPos(DEFAULT_GUN_POS); // Todo: Move to config

            if (selectedGun == BLAST_DOUBLE)
            {
                gun->setGunPos(BLAST_DOUBLE_GUN_POS);
            }

            if (selectedGun == BLAST_DIFFUSER)
            {
                gun->setGunPos(DIFFUSER_GUN_POS);
            }
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
