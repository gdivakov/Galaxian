
#include "MilesView.h"
#include "Consts.h"
#include "PlayerShip.h"

const int MILES_UPDATE_DELTA = 500;

MilesView::MilesView(LevelBase* p_level) : Texture(p_level->getSystem()->getRenderer())
{
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    level = p_level;
    milesPassed = 0;

    loadFromRenderedText(font, std::to_string(milesPassed), selectedOptionColor);
}

MilesView::~MilesView()
{
    TTF_CloseFont(font);

    font = NULL;
    level = NULL;
}

void MilesView::handleRender()
{
    int windowWidth = level->getSystem()->getWindowSize()->w;
    Vector2 pos(windowWidth - size.w - 16, 16);
    PlayerShip* player = (PlayerShip*) level->getPlayer();

    if (player && player->getMilesPassed() > milesPassed + MILES_UPDATE_DELTA)
    {
        milesPassed = player->getMilesPassed();
        milesPassed = milesPassed - (milesPassed % 500);

        loadFromRenderedText(font, std::to_string(milesPassed), selectedOptionColor);
    }

    render(pos);
}