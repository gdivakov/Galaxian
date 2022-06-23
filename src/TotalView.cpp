#include "TotalView.h"
#include "PlayerShip.h"

const std::string TITLE = "Level  passed!";
const std::string NEXT_LEVEL_TEXT = "Next  level  (coming soon)";
const std::string QUIT_TEXT = "Quit";
const std::string MILES_PASSED_TEXT = "- Miles  passed:  ";
const std::string ENEMIES_KILLED_TEXT = "- Enemies  killed:  ";

std::vector<std::string> scoreTexts = 
{
    TITLE,
    MILES_PASSED_TEXT,
    ENEMIES_KILLED_TEXT,
};

std::vector<std::string> buttonTexts =
{
   NEXT_LEVEL_TEXT,
   QUIT_TEXT
};

TotalView::TotalView(LevelBase* p_level)
{
	level = p_level;
	fontLarge = TTF_OpenFont(FONT_PATH.c_str(), LARGE_FONT_SIZE);
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    selectedOption = QUIT_TEXT;

    initButtons();
}

void TotalView::initScore()
{
    PlayerShip* player = (PlayerShip*)level->getPlayer();
    int milesPassed = player->getMilesPassed();
    int enemiesKilled = level->getSpawner()->getSpawnedEnemiesCount();

    for (std::string &el : scoreTexts)
    {
        bool isTitle = el == TITLE;
        scoreTextures.emplace(el, new Texture(level->getSystem()->getRenderer()));
        std::string text = el;

        if (el == MILES_PASSED_TEXT)
        {
            text = el + std::to_string(milesPassed);
        }

        if (el == ENEMIES_KILLED_TEXT)
        {
            text = el + std::to_string(enemiesKilled);
        }

        scoreTextures[el]->loadFromRenderedText(isTitle ? fontLarge : font, text, textColor);
    }
}

void TotalView::initButtons()
{
    // Clear prev buttons
    for (auto& el : buttonTextures)
    {
        delete el.second;
    }
    buttonTextures.clear();

    for (std::string& el : buttonTexts)
    {
        buttonTextures.emplace(el, new Texture(level->getSystem()->getRenderer()));

        SDL_Color color = textColor;
        
        if (el == selectedOption)
        {
            color = selectedOptionColor;

            if (el == NEXT_LEVEL_TEXT)
            {
                color = selectedDisabledOptionColor;
            }
        }

        buttonTextures[el]->loadFromRenderedText(font, el, color);
    }
}

TotalView::~TotalView()
{
    for (auto& el : scoreTextures)
    {
        delete el.second;
    }

    for (auto& el : buttonTextures)
    {
        delete el.second;
    }

    scoreTextures.clear();
    buttonTextures.clear();

	TTF_CloseFont(font);
    TTF_CloseFont(fontLarge);

	font = NULL;
    fontLarge = NULL;
    level = NULL;
}

void TotalView::handleRender()
{
    if (!isActive)
    {
        return;
    }

    SDL_Renderer* renderer = level->getSystem()->getRenderer();

    SDL_Rect rect =
    {
        WINDOWED_WIDTH / 14,
        WINDOWED_HEIGHT / 14,
        WINDOWED_WIDTH - WINDOWED_WIDTH / 7,
        WINDOWED_HEIGHT - WINDOWED_HEIGHT / 7
    };

    SDL_SetRenderDrawColor(renderer, 0x01, 0x62, 0xb1, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    int marginTop = rect.h/2.5;

    for (auto& el : scoreTextures)
    {
        bool isTitle = el.first == TITLE;

        Texture* text = el.second;
        Vector2 pos = isTitle ?
            Vector2(rect.x + (rect.w - text->size.w) / 2, rect.y + 24) :
            Vector2(rect.x + rect.w/3, rect.y + marginTop);

        text->render(pos);
        marginTop += isTitle ? 0 : 48;
    }

    bool isFirst = true;

    for (auto& el : buttonTextures)
    {
        Texture* text = el.second;
        int marginLeft = isFirst ? 48 : rect.w - text->size.w - 48;
        Vector2 pos = Vector2(rect.x + marginLeft, rect.y + rect.h - text->size.h - 24);
        
        isFirst = false;

        if (selectedOption == el.first)
        {
            SDL_Rect buttonRect =
            {
                pos.x - 5,
                pos.y,
                text->size.w + 10,
                text->size.h - 3
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &buttonRect);
            SDL_RenderDrawRect(renderer, &buttonRect);
        }

        text->render(pos);
    }
}

void TotalView::handleEvent(SDL_Event& e)
{
    if (!isActive || e.type != SDL_KEYDOWN)
    {
        return;
    }

    if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
    {
        if (selectedOption == QUIT_TEXT)
        {
            level->quit();
            return;
        }
    }

    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_a:
        if (selectedOption == QUIT_TEXT)
        {
            level->getSystem()->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
            selectedOption = NEXT_LEVEL_TEXT;
            initButtons();
        }
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        if (selectedOption == NEXT_LEVEL_TEXT)
        {
            level->getSystem()->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
            selectedOption = QUIT_TEXT;
            initButtons();
        }
        break;
    }
}