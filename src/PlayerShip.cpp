#include "PlayerShip.h"
#include "Consts.h"

PlayerShip::PlayerShip(
    const App* p_system, 
    LevelBase* p_level, 
    ShipParams params) :
	Ship(p_system, params, p_level) 
{
    pos = Vector2((WINDOWED_WIDTH - getWidth())/2, WINDOWED_HEIGHT - getHeight() - 20);
}

void PlayerShip::handleEvent(SDL_Event& e)
{
    if (level->isPaused)
    {
        return;
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

    gun->handleEvent(e);

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
    Vector2 center(size.w/2, size.h/2);
    render(pos - center, currentClip);

    for (int i = 0; i < colliders.size(); i++)
    {
        SDL_RenderDrawRect(renderer, &colliders[i]);
    }

    DrawCircle(renderer, wrapperCollider.pos.x, wrapperCollider.pos.y, wrapperCollider.r);
}