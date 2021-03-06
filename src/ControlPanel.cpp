#include "ControlPanel.h"
#include "Vector2.h"
#include "SoundConst.h"
#include "Consts.h"

ControlPanel::ControlPanel(SDL_Renderer* p_renderer, const App* p_system, MainScreen* p_mainScreenPt)
{
    renderer = p_renderer;
    system = p_system;
    mainScreenPt = p_mainScreenPt;
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    smallFont = TTF_OpenFont(FONT_PATH.c_str(), SMALL_FONT_SIZE);
    selectedOptionIdx = MENU_START_GAME;
    isSettingsOpened = false;
    isActive = true;
    settingsView = new Settings(system, isSettingsOpened);
    
    loadOptions();
}

void ControlPanel::onBeforeRender()
{
    if (!isActive)
    {
        return;
    }

    if (isSettingsOpened)
    {
        settingsView->handleRender();
        return;
    }

    renderOptions();
}

void ControlPanel::renderOptions()
{
    const Size* wSize = system->getWindowSize();
    for (int i = 0, offset = 10; i < MENU_OPTION_NAMES.size(); i++, offset += 40)
    {
        Texture* option = options[i];

        int offsetHeight = (wSize->h - (option->size.h * 3)) / 2;
        int offsetWidth = (wSize->w - option->size.w) / 2 + 200;

        // Hightlight selected option
        if (selectedOptionIdx == i)
        {
            SDL_Point selectedOptionPos = { offsetWidth, offsetHeight + offset };

            SDL_Rect rect = {
                selectedOptionPos.x - 5,
                selectedOptionPos.y,
                options[i]->size.w + 10,
                options[i]->size.h - 3,
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }

        option->render(Vector2(offsetWidth, offsetHeight + offset));
    }

    tooltip->render(
        Vector2(
            (wSize->w - tooltip->size.w)/2,
            wSize->h - tooltip->size.h - 16
        )
    );
}

void ControlPanel::handleEvent(SDL_Event& e)
{
    if (!isActive)
    {
        return;
    }

    if (isSettingsOpened)
    {
        settingsView->handleEvent(e);
        return;
    }

    if (e.type != SDL_KEYDOWN)
    {
        return;
    }

    char keyDown = e.key.keysym.scancode;
    int nextSelectedOptionIdx;

    if (keyDown == SDL_SCANCODE_RETURN)
    {
        if (selectedOptionIdx == MENU_START_GAME)
        {
            mainScreenPt->handleCompleted();
            return;
        }

        if (selectedOptionIdx == MENU_SETTINGS)
        {
            isSettingsOpened = true;
            return;
        }

        if (selectedOptionIdx == MENU_QUIT)
        {

            mainScreenPt->quit();
            return;
        }
    }

    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
    case SDLK_w:
        nextSelectedOptionIdx = selectedOptionIdx - 1 < 0 ? options.size() - 1 : selectedOptionIdx - 1;
        updateSelectedOption(nextSelectedOptionIdx);
        system->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
        break;
    case SDLK_DOWN:
    case SDLK_s:
        nextSelectedOptionIdx = selectedOptionIdx + 1 > options.size() - 1 ? 0 : selectedOptionIdx + 1;
        updateSelectedOption(nextSelectedOptionIdx);
        system->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
        break;
    }
}

void ControlPanel::loadOptions()
{
    for (int i = 0; i < MENU_OPTION_NAMES.size(); i++)
    {
        Texture* textTexture = new Texture(renderer);

        textTexture->loadFromRenderedText(
            font,
            MENU_OPTION_NAMES[i],
            selectedOptionIdx == i ? selectedOptionColor : textColor
        );

        options.push_back(textTexture);
    }

    // Load tooltip
    tooltip = new Texture(renderer);
    tooltip->loadFromRenderedText(
        smallFont,
        TOOLTIP_TEXT,
        textColor
    );
}

void ControlPanel::updateSelectedOption(int nextIdx)
{
    options[selectedOptionIdx]->loadFromRenderedText(
        font,
        MENU_OPTION_NAMES[selectedOptionIdx],
        textColor
    );

    options[nextIdx]->loadFromRenderedText(
        font,
        MENU_OPTION_NAMES[nextIdx],
        selectedOptionColor
    );

    selectedOptionIdx = nextIdx;
}

ControlPanel::~ControlPanel()
{
    delete tooltip;
    delete settingsView;

    for (int i = 0; i < options.size(); i++)
    {
        delete options[i];
    }

    options.clear();
    TTF_CloseFont(font);
    TTF_CloseFont(smallFont);

    tooltip = NULL;
    settingsView = NULL;
    font = NULL;
    smallFont = NULL;
    renderer = NULL;
}