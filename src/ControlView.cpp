#include "ControlView.h"

namespace control
{
    struct Row
    {
        std::string fImagePath;
        std::string text;
        std::string sImagePath;
    };

    const std::vector<Row> rowPaths
    {
        { "res/images/arrows.png", "move", "res/images/wasd.png"},
        { "res/images/space.png", "shoot", "res/images/l_key.png" },
        { "res/images/q_key.png", "rotate", "res/images/e_key.png" },
        { "res/images/f_key.png", "weapon switch", "res/images/f_key.png" },
    };
}

ControlView::ControlView(LevelBase* p_level, bool& p_isActive) : isActive(p_isActive)
{
	level = p_level;
    font = TTF_OpenFont(FONT_PATH.c_str(), MEDIUM_FONT_SIZE);

    catTexture = new Texture(level->getSystem()->getRenderer());
    catTexture->loadFromFile("res/images/cat.png");

    initRows();
}

ControlView::~ControlView()
{
    TTF_CloseFont(font);

    for (auto& row : rows)
    {
        delete row.leftImage;
        delete row.rightImage;
        delete row.text;
    }

    delete catTexture;

    rows.clear();

    catTexture = nullptr;
    level = nullptr;
    font = nullptr;
}

void ControlView::initRows()
{
    SDL_Renderer* renderer = level->getSystem()->getRenderer();

    for (auto& row : control::rowPaths)
    {
        ControlRow nextRow = { new Texture(renderer), new Texture(renderer), new Texture(renderer) };

        nextRow.leftImage->loadFromFile(row.fImagePath);
        nextRow.text->loadFromRenderedText(font, row.text, textColor);
        nextRow.rightImage->loadFromFile(row.sImagePath);

        rows.emplace_back(nextRow);
    }
}

void ControlView::handleRender()
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

    catTexture->render(Vector2(rect.x + (rect.w - catTexture->size.w)/2, marginTop));

    marginTop += catTexture->size.h + shift/2;

    for (auto& row : rows)
    {
        row.leftImage->render(Vector2(rect.x + 128, marginTop));
        row.rightImage->render(Vector2(rect.x + rect.w - row.rightImage->size.w - 128, marginTop));
        row.text->render(Vector2(rect.x + (rect.w - row.text->size.w) / 2, marginTop + shift));

        marginTop += row.leftImage->size.h + shift/10;
    }
}

void ControlView::handleEvent(SDL_Event& e)
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