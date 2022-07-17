#include <algorithm>
#include "Settings.h"
#include "Vector2.h"
#include "SoundConst.h"
#include "Consts.h"

Settings::Settings(const App* p_system, bool& p_isActive)
    :system(p_system), 
    renderer(p_system->getRenderer()),
    isActive(p_isActive)
{
    font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
    selectedIdx = 0;
    isConfirmSelected = false;
    confirmButton = NULL;
    config = readSettingsConfig();

    loadOptions();
}

Settings::~Settings()
{
    delete confirmButton;

    for (int i = 0; i < options.size(); i++)
    {
        delete options[i].optionTexture;
        delete options[i].valueTexture;
    }

    TTF_CloseFont(font);
    options.clear();
    font = NULL;
    confirmButton = NULL;
}

void Settings::handleRender()
{
    if (!isActive)
    {
        return;
    }

    render();
    renderConfirm();
}

void Settings::loadOptions()
{
    using namespace SETTINGS_FIELDS;

    // Load options
    for (auto& el : NAMES)
    {
        Types type = el.first;

        auto it = std::find(DISABLED_OPTIONS.begin(), DISABLED_OPTIONS.end(), type);
        bool isDisabled = it != DISABLED_OPTIONS.end();

        SettingsOption option =
        {
            new Texture(renderer),
            new Texture(renderer),
            getAvailableValues(type),
            type,
            config[type],
            isDisabled,
        };

        option.optionTexture->loadFromRenderedText(font, el.second, textColor);

        option.valueTexture->loadFromRenderedText(
            font, 
            option.availableValues[config[type]], 
            selectedIdx == type ? selectedOptionColor : textColor
        );

        options.push_back(option);
    }

    // Load confirm button 
    confirmButton = new Texture(renderer);
    confirmButton->loadFromRenderedText(
        font,
        CONFIRM_BUTTON_TEXT,
        isConfirmSelected ? selectedOptionColor : textColor
    );
}

void Settings::render()
{
    using namespace SETTINGS_FIELDS;
    
    const Size* wSize = system->getWindowSize();

    // Render settings panel
    SDL_Rect rect = {
        wSize->w / 14,
        wSize->h / 14,
        wSize->w - wSize->w / 7,
        wSize->h - wSize->h / 7
    };

    SDL_SetRenderDrawColor(renderer, 0x01, 0x62, 0xb1, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);

    // Render options
    SDL_Point selectedOptionPos;
    int margin = rect.h / (NAMES.size() + 1);

    for (int i = 0, offset = margin / 3; i < options.size(); i++, offset += margin)
    {
        Texture* option = options[i].optionTexture;
        Texture* displayedValue = options[i].valueTexture;

        int offsetHeight = rect.y + offset;
        int offsetWidth = rect.x + margin / 2;

        // Hightlight selected option
        if (selectedIdx == i && !isConfirmSelected)
        {
            SDL_Point selectedOptionPos = { rect.x + rect.w - displayedValue->size.w - margin / 2, offsetHeight };

            SDL_Rect rect = {
                selectedOptionPos.x - 5,
                selectedOptionPos.y,
                displayedValue->size.w + 10,
                displayedValue->size.h - 3,
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }

        option->render(Vector2(offsetWidth, offsetHeight));
        displayedValue->render(Vector2(rect.x + rect.w - displayedValue->size.w - margin / 2, offsetHeight));
    }
}

void Settings::updateSelectedOption(int nextIdx)
{
    using namespace SETTINGS_FIELDS;

    // Handle hover out
    if (nextIdx != options.size() && isConfirmSelected) // Confirm button
    {
        confirmButton->loadFromRenderedText(
            font,
            CONFIRM_BUTTON_TEXT,
            textColor
        );

        isConfirmSelected = false;
    }
    else { // Settings option value
        SettingsOption selectedOption = options[selectedIdx];
        options[selectedIdx].valueTexture->loadFromRenderedText(
            font,
            selectedOption.availableValues[selectedOption.value],
            textColor
        );
    }

    // Handle hover in
    if (nextIdx == options.size()) // Confirm button
    {
        confirmButton->loadFromRenderedText(
            font,
            CONFIRM_BUTTON_TEXT,
            selectedOptionColor
        );

        isConfirmSelected = true;
    }
    else { // Settings option value
        SettingsOption nextOption = options[nextIdx];
        nextOption.valueTexture->loadFromRenderedText(
            font,
            nextOption.availableValues[nextOption.value],
            nextOption.isDisabled ? selectedDisabledOptionColor : selectedOptionColor
        );
    }

    selectedIdx = nextIdx;
}

void Settings::updateValue()
{
    using namespace SETTINGS_FIELDS;

    SettingsOption updatedOption = options[selectedIdx];

    if (updatedOption.isDisabled)
    {
        return;
    }

    int nextValue = updatedOption.value + 1 < updatedOption.availableValues.size() ? updatedOption.value + 1 : 0;
    std::string nextTextValue = updatedOption.availableValues[nextValue];

    config[selectedIdx] = nextValue;
    options[selectedIdx].value = nextValue;
    options[selectedIdx].valueTexture->loadFromRenderedText(font, nextTextValue, selectedOptionColor);

    bool isMuted;

    switch (selectedIdx)
    {
    case MUSIC:
        isMuted = system->getAudioPlayer()->isMusicMuted;
        system->getAudioPlayer()->setMuted(!isMuted);
        break;
    case SOUNDS:
        isMuted = system->getAudioPlayer()->isSoundsMuted;

        system->getAudioPlayer()->setMuted(!isMuted, false);
        break;
    }
}

void Settings::renderConfirm()
{
    SDL_Rect rect = {
        WINDOWED_WIDTH / 14,
        WINDOWED_HEIGHT / 14,
        WINDOWED_WIDTH - WINDOWED_WIDTH / 7,
        WINDOWED_HEIGHT - WINDOWED_HEIGHT / 7
    };

    int buttonWidth = confirmButton->size.w;
    int buttonHeight = confirmButton->size.h;
    int offsetWidth = rect.x + (rect.w - buttonWidth) / 2;
    int offsetHeight = rect.y + rect.h - buttonHeight - 16;

    // Hightlight selected option
    if (isConfirmSelected)
    {
        SDL_Point selectedOptionPos = { offsetWidth, offsetHeight };

        SDL_Rect selectedRect = {
            selectedOptionPos.x - 5,
            selectedOptionPos.y,
            buttonWidth + 10,
            buttonHeight - 3,
        };

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &selectedRect);
    }

    confirmButton->render(Vector2(offsetWidth, offsetHeight));
}

void Settings::handleEvent(SDL_Event& e)
{
    if (!isActive || e.type != SDL_KEYDOWN || e.key.repeat == 1)
    {
        return;
    }

    char keyDown = e.key.keysym.scancode;

    if (keyDown == SDL_SCANCODE_RETURN)
    {
        if (isConfirmSelected)
        {
            close();
            return;
        }

        updateValue();

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
        break;
    case SDLK_DOWN:
    case SDLK_s:
        if (selectedIdx + 1 <= options.size())
        {
            updateSelectedOption(selectedIdx + 1);
            system->getAudioPlayer()->playSound(SELECT_ITEM_SOUND);
        }
        break;
    case SDLK_ESCAPE:
        close();
    }
}

void Settings::close()
{
    writeSettingsConfig(config);
    updateSelectedOption(0);

    isActive = false;
}

