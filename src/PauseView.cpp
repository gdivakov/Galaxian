#include <vector>

#include "PauseView.h"
#include "Consts.h"
#include "Vector2.h"
#include "SoundConst.h"
#include "Loop.h"

PauseView::PauseView(LevelBase* p_level, Hood* p_hood)
    : renderer(p_level->getSystem()->getRenderer()), level(p_level), system(p_level->getSystem())
{
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    selectedIdx = PAUSE_FIELDS::RESUME;
    isSettingsActive = false;
    isControlActive = false;
    isBuffDescActive = false;
    parentHood = p_hood;

    settingsView = new Settings(system, isSettingsActive);
    controlView = new ControlView(level, isControlActive);
    buffDescView = new BuffDescView(level, isBuffDescActive);

    loadOptions();
}

PauseView::~PauseView()
{
    for (auto& el : options)
    {
        delete el.optionTexture;
    }

    delete settingsView;
    delete controlView;

    TTF_CloseFont(font);
    options.clear();

    font = nullptr;
    level = nullptr;
    parentHood = nullptr;
    settingsView = nullptr;
    controlView = nullptr;
}

void PauseView::loadOptions()
{
    using namespace PAUSE_FIELDS;

    for (auto& pair : NAMES)
    {
        PauseOption nextOption = { new Texture(renderer), pair.first };

        nextOption.optionTexture->loadFromRenderedText(
            font,
            pair.second,
            pair.first == RESUME ? selectedOptionColor : textColor
        );

        options.push_back(nextOption);
    }
}

void PauseView::onBeforeRender()
{
    using namespace PAUSE_FIELDS;

    // Render settings panel
    SDL_Rect rect = {
        WINDOWED_WIDTH / 14,
        WINDOWED_HEIGHT / 14,
        WINDOWED_WIDTH - WINDOWED_WIDTH / 7,
        WINDOWED_HEIGHT - WINDOWED_HEIGHT / 7
    };

    SDL_SetRenderDrawColor(renderer, 0x01, 0x62, 0xb1, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);

    // Render options
    SDL_Point selectedOptionPos;
    int margin = rect.h / (NAMES.size() + 3);

    for (int i = 0, offset = margin * 2; i < options.size(); i++, offset += margin)
    {
        PauseOption option = options[i];
        std::string displayedValue = NAMES.at(option.fieldType);

        int offsetHeight = rect.y + offset;
        int offsetWidth = rect.x + (rect.w - option.optionTexture->getWidth()) / 2;

        // Hightlight selected option
        if (selectedIdx == i)
        {
            SDL_Rect rect = {
                offsetWidth - 5,
                offsetHeight,
                option.optionTexture->getWidth() + 10,
                option.optionTexture->getHeight() - 3,
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }

        option.optionTexture->render(Vector2(offsetWidth, offsetHeight));
    }

    settingsView->handleRender();
    controlView->handleRender();
    buffDescView->handleRender();
}
	
void PauseView::handleEvent(SDL_Event& e)
{
    using namespace PAUSE_FIELDS;

    if (hasNestedActive())
    {
        settingsView->handleEvent(e);
        controlView->handleEvent(e);
        buffDescView->handleEvent(e);
        return;
    }

    if (e.type != SDL_KEYDOWN)
    {
        return;
    }

    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
    case SDLK_w:
        if (selectedIdx - 1 >= 0)
        {
            updateSelectedOption(selectedIdx - 1);
            system->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
        }
        return;
    case SDLK_DOWN:
    case SDLK_s:
        if (selectedIdx + 1 < options.size())
        {
            updateSelectedOption(selectedIdx + 1);
            system->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
        }
        return;
    }

    if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
    {
        switch (selectedIdx)
        {
        case RESUME:
            return parentHood->handleResumed();
        case SETTINGS:
            isSettingsActive = true;
            return;
        case CONTROL:
            isControlActive = true;
            return;
        case BUFF_DESCRIPTION:
            isBuffDescActive = true;
            return;
        case QUIT:
            level->quit();
            return;
        }
    }
}

void PauseView::updateSelectedOption(int nextIdx)
{
    using namespace PAUSE_FIELDS;

    std::string optionText = NAMES.at(options[selectedIdx].fieldType);
    std::string nextOptionText = NAMES.at(options[nextIdx].fieldType);

    options[selectedIdx].optionTexture->loadFromRenderedText(
        font,
        optionText,
        textColor
    );

    options[nextIdx].optionTexture->loadFromRenderedText(
        font,
        nextOptionText,
        selectedOptionColor
    );

    selectedIdx = nextIdx;
}