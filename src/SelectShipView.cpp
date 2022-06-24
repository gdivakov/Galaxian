#include "SelectShipView.h"
#include "Consts.h"
#include "MainScreen.h"
#include "SettingsConsts.h"

const std::string PREVIEW_TEXT = "Choose  the  ship";

SelectShipView::SelectShipView(LevelBase* p_level)
{
	level = p_level;
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    isActive = false;
    isShipSelected = false;
    selectedShipIdx = 0;
    SDL_Renderer* renderer = level->getSystem()->getRenderer();

    Texture* shipA = new Texture(renderer);
    shipA->loadFromSprite(SONIC_A_SHIP_PREVIEW);

    Texture* shipB = new Texture(renderer);
    shipB->loadFromSprite(SONIC_B_SHIP_PREVIEW);

    Texture* shipC = new Texture(renderer);
    shipC->loadFromSprite(SONIC_C_SHIP_PREVIEW);

    text = new Texture(renderer);
    text->loadFromRenderedText(font, PREVIEW_TEXT, selectedOptionColor);

    ships.push_back({ 0, shipA });
    ships.push_back({ 0, shipB });
    ships.push_back({ 0, shipC });
}

SelectShipView::~SelectShipView()
{
    for (int i = 0; i < ships.size(); i++)
    {
        delete ships[i].sprite;
    }

    delete text;

    TTF_CloseFont(font);
    ships.clear();

    level = NULL;
    font = NULL;
}

void SelectShipView::onBeforeRender()
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

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawRect(renderer, &rect);

    SDL_Rect selected =
    {
        rect.x + selectedShipIdx * rect.w / 3,
        rect.y,
        rect.w / 3,
        rect.h,
    };

    SDL_SetRenderDrawColor(renderer, 0x01, 0x62, 0xb1, 0xFF);
    SDL_RenderFillRect(renderer, &selected);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &selected);

    int marginRight = rect.w / 3;
    int shiftX = marginRight / 4.5;

    for (int i = 0; i < ships.size(); i++)
    {
        std::vector<SDL_Rect>& shipClips = ships[i].sprite->getClips();
        SDL_Rect* currentClip = &shipClips[ships[i].frame / shipClips.size()];
        int marginTop = rect.y + (rect.h - ships[i].sprite->size.h) / 2;

        ships[i].sprite->render(Vector2(rect.x + shiftX, marginTop), currentClip);
        shiftX += marginRight;
    }

    SDL_Rect textBlock =
    {
        rect.x,
        rect.y,
        rect.w,
        text->size.h,
    };

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &textBlock);

    SDL_Rect bottomBlock =
    {
        rect.x,
        rect.y + rect.h - text->size.h,
        rect.w,
        text->size.h,
    };

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &bottomBlock);

    text->render(Vector2(rect.x + (rect.w - text->size.w)/2, rect.y));
    text->render(Vector2(rect.x + (rect.w - text->size.w) / 2, rect.y + rect.h - text->size.h));
}

void SelectShipView::onAfterRender()
{
    for (int i = 0; i < ships.size(); i++)
    {
        int clipLength = ships[i].sprite->getClips().size();
        ships[i].frame++;

        if (ships[i].frame / clipLength >= clipLength)
        {
            ships[i].frame = 0;
        }
    }
}

void SelectShipView::handleEvent(SDL_Event& e)
{
    if (!isActive || e.type != SDL_KEYDOWN)
    {
        return;
    }

    switch (e.key.keysym.sym)
    {
    case SDLK_a:
    case SDLK_LEFT:
        selectedShipIdx = selectedShipIdx == 0 ? 0 : selectedShipIdx - 1;
        break;
    case SDLK_d:
    case SDLK_RIGHT:
        selectedShipIdx = selectedShipIdx == ships.size() - 1 ? selectedShipIdx : selectedShipIdx + 1;
        break;
    case SDLK_RETURN:
        isShipSelected = true;
        
        std::vector<int> config = readSettingsConfig();
        
        config[SETTINGS_FIELDS::SELECTED_SHIP] = selectedShipIdx;
        writeSettingsConfig(config);

        MainScreen* mainScreenP = (MainScreen*) level;
        mainScreenP->handleCompleted();
        break;
    }
}

void SelectShipView::show()
{
    isActive = true;
}