#include "BuffDescView.h"

namespace buffDesc
{
    struct Row
    {
        std::string imagePath;
        std::string text;
    };

    const std::vector<Row> rowPaths
    {
        { "res/icons/buffs/circled/armorUp.png", "Restore armor" },
        { "res/icons/buffs/circled/healthUp.png", "Restore health" },
        { "res/icons/buffs/circled/breakHand.png", "Collide enemies to break them. Still vulnarable to bullets  (5s)" },
        { "res/icons/buffs/circled/saveHand.png", "Save from death and restore health  (30s)" },
        { "res/icons/buffs/circled/shield.png", "Block bullets by shield  (10s)" },
        { "res/icons/buffs/circled/speedUp.png", "Speed up ship  (5s)" },
        { "res/icons/buffs/circled/superpower.png", "Ship is invulnerable  (15s)" },
    };

    const int CUSTOM_FONT_SIZE = 27;

    const std::string TITLE = "Buffs and amplifiers";
}

BuffDescView::BuffDescView(LevelBase* p_level, bool& p_isActive) : isActive(p_isActive)
{
    level = p_level;
    font = TTF_OpenFont(FONT_PATH.c_str(), buffDesc::CUSTOM_FONT_SIZE);
    fontTitle = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);

    title = new Texture(level->getSystem()->getRenderer());
    title->loadFromRenderedText(fontTitle, buffDesc::TITLE, textColor);

    initRows();
}

BuffDescView::~BuffDescView()
{
    TTF_CloseFont(font);
    TTF_CloseFont(fontTitle);

    for (auto& row : rows)
    {
        delete row.image;
        delete row.text;
    }

    delete title;

    rows.clear();

    title = nullptr;
    level = nullptr;
    font = nullptr;
    fontTitle = nullptr;
}

void BuffDescView::initRows()
{
    SDL_Renderer* renderer = level->getSystem()->getRenderer();

    for (auto& row : buffDesc::rowPaths)
    {
        DescRow nextRow = { new Texture(renderer), new Texture(renderer) };

        nextRow.image->loadFromFile(row.imagePath);
        nextRow.text->loadFromRenderedText(font, row.text, textColor);

        rows.emplace_back(nextRow);
    }
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

    int shift = 16;
    int marginTop = rect.y + shift;

    title->render(Vector2(rect.x + (rect.w - title->size.w)/2, marginTop));

    marginTop += title->size.h;

    for (auto& row : rows)
    {
        row.image->render(Vector2(rect.x + shift * 2, marginTop));
        row.text->render(Vector2(rect.x + 50 + shift * 3, marginTop + (row.image->size.h - row.text->size.h)/2));

        marginTop += row.image->size.h + shift;
    }
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