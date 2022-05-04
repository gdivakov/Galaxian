
#include "MilesView.h"
#include "Consts.h"

const int MILES_UPDATE_DELTA = 500;

MilesView::MilesView(LevelBase* p_level) : Texture(p_level->getSystem()->getRenderer())
{
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    timer = new Timer();
    timer->start();
    milesPassed = 0;
    level = p_level;

    loadFromRenderedText(font, std::to_string(milesPassed), selectedOptionColor);
}

MilesView::~MilesView()
{
    delete timer;
    TTF_CloseFont(font);

    font = NULL;
    timer = NULL;
    level = NULL;
}

void MilesView::handleRender()
{
    Vector2 pos(level->getSystem()->getWindowSize()->w - size.w - 16, 16);

    if (timer->getTicks() > milesPassed + MILES_UPDATE_DELTA && level->getPlayer())
    {
        milesPassed += MILES_UPDATE_DELTA;

        loadFromRenderedText(font, std::to_string(milesPassed), selectedOptionColor);
    }

    render(pos);
}

void MilesView::handlePaused()
{
    timer->pause();
}

void MilesView::handleResumed()
{
    timer->unpause();
}
