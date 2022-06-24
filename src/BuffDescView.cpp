#include "BuffDescView.h"

// 7 icons 
// res/icons/buffs/circled

BuffDescView::BuffDescView(LevelBase* p_level, bool& p_isActive) : isActive(p_isActive)
{
    level = p_level;
}

BuffDescView::~BuffDescView()
{
    level = nullptr;
}

void BuffDescView::handleRender()
{
    if (!isActive)
    {
        return;
    }

    SDL_Renderer* renderer = level->getSystem()->getRenderer();

    SDL_Rect rect = {
        WINDOWED_WIDTH / 14, // Todo: Replace by system->getWindowSize()
        WINDOWED_HEIGHT / 14,
        WINDOWED_WIDTH - WINDOWED_WIDTH / 7,
        WINDOWED_HEIGHT - WINDOWED_HEIGHT / 7
    };

    SDL_SetRenderDrawColor(renderer, 0x01, 0x62, 0xb1, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);
}

void BuffDescView::handleEvent(SDL_Event& e)
{
    if (!isActive || e.type != SDL_KEYDOWN || e.key.repeat == 1)
    {
        return;
    }

    if (e.key.keysym.scancode == SDL_SCANCODE_RETURN || e.key.keysym.sym == SDLK_ESCAPE)
    {
        isActive = false;
        return;
    }
}