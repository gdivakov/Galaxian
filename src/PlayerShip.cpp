#include "PlayerShip.h"

PlayerShip::PlayerShip(
    const App* p_system,
    LevelBase* p_level,
    ShipType type
    ) :
    Ship(p_system, getShipParams(type), p_level, false)
{
    pos = Vector2((WINDOWED_WIDTH)/2, WINDOWED_HEIGHT - getHeight() - 20);
    rotation = 0;
}

void PlayerShip::handleEvent(SDL_Event& e)
{
    if (level->isPaused || !health)
    {
        return;
    }

    gun->handleEvent(e);

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
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
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
    if (!level->isPaused)
    {
        move();
    }

    gun->onBeforeRender();

    std::vector<SDL_Rect>& shipClips = getClips();
    SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

    render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);

    //showColliders();
}

