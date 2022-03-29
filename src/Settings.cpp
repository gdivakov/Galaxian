#include "Settings.h"

Settings::Settings(const App* p_system, bool& p_isOpened)
    :system(p_system), 
    renderer(p_system->getRenderer()),
    isOpened(p_isOpened)
{
    font = TTF_OpenFont("res/Staatliches-Regular.ttf", 35);
    selectedSettingsIdx = 0;
    isSettingsConfirmSelected = false;
    settingsConfirmButton = NULL;

    loadOptions();
}

void Settings::handleRender()
{
    render();
    renderConfirm();
}

void Settings::loadOptions()
{
    for (int i = 0; i < NAMES.size(); i++)
    {
        Texture* optionsTextTexture = new Texture(renderer);
        Texture* valueTextTexture = new Texture(renderer);
        OptionType type = i != LANGUAGE_IDX ? SWITCHABLE : LANGUAGE;

        optionsTextTexture->loadFromRenderedText(
            font,
            NAMES[i],
            textColor
        );

        valueTextTexture->loadFromRenderedText(
            font,
            type == SWITCHABLE ?
            STATUSES[getOptionValue(i, type)] :
            SUPPORTED_LANGUAGES[ENGLISH],
            selectedSettingsIdx == i ? selectedOptionColor : textColor
        );

        SettingsOption option =
        {
            optionsTextTexture,
            valueTextTexture,
            type == getOptionValue(i, type),
            type,
            type == LANGUAGE || i == FULLSCREEN_IDX, // isDisabled option (not supported now)
        };

        settingsOptions.push_back(option);
    }

    // Load confirm button 
    settingsConfirmButton = new Texture(renderer);
    settingsConfirmButton->loadFromRenderedText(
        font,
        CONFIRM_BUTTON_TEXT,
        isSettingsConfirmSelected ? selectedOptionColor : textColor
    );
}

void Settings::render()
{
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
    int margin = rect.h / (NAMES.size() + 1);

    for (int i = 0, offset = margin / 3; i < NAMES.size(); i++, offset += margin)
    {
        Texture* option = settingsOptions[i].option;
        Texture* displayedValue = settingsOptions[i].displayedValue;

        int offsetHeight = rect.y + offset;
        int offsetWidth = rect.x + margin / 2;

        // Hightlight selected option
        if (selectedSettingsIdx == i && !isSettingsConfirmSelected)
        {
            SDL_Point selectedOptionPos = { rect.x + rect.w - displayedValue->getWidth() - margin / 2, offsetHeight };

            SDL_Rect rect = {
                selectedOptionPos.x - 5,
                selectedOptionPos.y,
                displayedValue->getWidth() + 10,
                displayedValue->getHeight() - 3,
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }

        option->render(offsetWidth, offsetHeight);
        displayedValue->render(rect.x + rect.w - displayedValue->getWidth() - margin / 2, offsetHeight);
    }
}

void Settings::updateSelectedOption(int nextIdx)
{
    // Hover out confirm button
    if (nextIdx != settingsOptions.size() && isSettingsConfirmSelected)
    {
        settingsConfirmButton->loadFromRenderedText(
            font,
            CONFIRM_BUTTON_TEXT,
            textColor
        );

        isSettingsConfirmSelected = false;
    }
    else {
        // Hover out settings option
        SettingsOption selectedOption = settingsOptions[selectedSettingsIdx];

        std::string optionText = selectedOption.type == SWITCHABLE ?
            STATUSES[selectedOption.value] :
            SUPPORTED_LANGUAGES[selectedOption.value];

        settingsOptions[selectedSettingsIdx].displayedValue->loadFromRenderedText(
            font,
            optionText,
            textColor
        );
    }

    // Hover in confirm button selection
    if (nextIdx == settingsOptions.size())
    {
        settingsConfirmButton->loadFromRenderedText(
            font,
            CONFIRM_BUTTON_TEXT,
            selectedOptionColor
        );

        isSettingsConfirmSelected = true;
    }
    else {
        // Hover out settings option
        SettingsOption nextOption = settingsOptions[nextIdx];

        std::string optionText = nextOption.type == SWITCHABLE ?
            STATUSES[nextOption.value] :
            SUPPORTED_LANGUAGES[nextOption.value];

        // Hover in settings option
        settingsOptions[nextIdx].displayedValue->loadFromRenderedText(
            font,
            optionText,
            nextOption.isDisabled ? selectedDisabledOptionColor : selectedOptionColor
        );
    }

    selectedSettingsIdx = nextIdx;
}

void Settings::updateValue() // Todo: save on disk
{
    int nextValue;
    std::string nextTextValue;
    SettingsOption updatedOption = settingsOptions[selectedSettingsIdx];

    if (updatedOption.isDisabled)
    {
        return;
    }

    if (updatedOption.type == LANGUAGE)
    {
        int nextLanguageIdx = updatedOption.value + 1 >= SUPPORTED_LANGUAGES.size() ? 0 : updatedOption.value + 1;
        nextValue = SupportedLanguages(nextLanguageIdx);
        nextTextValue = SUPPORTED_LANGUAGES[nextValue];
    }
    else {
        bool isDisabled = settingsOptions[selectedSettingsIdx].value == DISABLED;
        nextValue = isDisabled ? ENABLED : DISABLED;
        nextTextValue = STATUSES[nextValue];

        switch (selectedSettingsIdx)
        {
        case MUSIC_IDX:
            system->getAudioPlayer()->toggleMute();
            break;
        case SOUNDS_IDX:
            system->getAudioPlayer()->toggleMute(false);
            break;
        }
    }

    settingsOptions[selectedSettingsIdx].value = nextValue;
    settingsOptions[selectedSettingsIdx].displayedValue->loadFromRenderedText(
        font,
        nextTextValue,
        selectedOptionColor
    );
}

void Settings::renderConfirm()
{
    SDL_Rect rect = {
        WINDOWED_WIDTH / 14,
        WINDOWED_HEIGHT / 14,
        WINDOWED_WIDTH - WINDOWED_WIDTH / 7,
        WINDOWED_HEIGHT - WINDOWED_HEIGHT / 7
    };

    int buttonWidth = settingsConfirmButton->getWidth();
    int buttonHeight = settingsConfirmButton->getHeight();
    int offsetWidth = rect.x + (rect.w - buttonWidth) / 2;
    int offsetHeight = rect.y + rect.h - buttonHeight - 16;

    // Hightlight selected option
    if (isSettingsConfirmSelected)
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

    settingsConfirmButton->render(offsetWidth, offsetHeight);
}

int Settings::getOptionValue(int idx, OptionType type)
{
    int nextValue = 0;

    switch (type)
    {
    case SWITCHABLE:
        if (idx == MUSIC_IDX)
        {
            nextValue = !system->getAudioPlayer()->isMusicMuted;
        }

        if (idx == SOUNDS_IDX)
        {
            nextValue = !system->getAudioPlayer()->isSoundsMuted;
        }
        break;
    case LANGUAGE:
        break;
    }
    return nextValue;
}

void Settings::handleEvent(SDL_Event& e)
{
    if (!isOpened || e.type != SDL_KEYDOWN)
    {
        return;
    }

    char keyDown = e.key.keysym.scancode;
    int nextSelectedSettingsIdx;

    if (keyDown == SDL_SCANCODE_RETURN)
    {
        if (isSettingsConfirmSelected)
        {
            // Close settings
            updateSelectedOption(0);

            isOpened = false;
        }
        else {
            updateValue();
        }

        return;
    }

    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
    case SDLK_w:
        if (selectedSettingsIdx - 1 >= 0)
        {
            nextSelectedSettingsIdx = selectedSettingsIdx - 1;
            updateSelectedOption(nextSelectedSettingsIdx);
        }
        break;
    case SDLK_DOWN:
    case SDLK_s:
        if (selectedSettingsIdx + 1 <= settingsOptions.size())
        {
            nextSelectedSettingsIdx = selectedSettingsIdx + 1;
            updateSelectedOption(nextSelectedSettingsIdx);
        }
        break;
    }
}

Settings::~Settings()
{
    delete settingsConfirmButton;

    for (int i = 0; i < settingsOptions.size(); i++)
    {
        delete settingsOptions[i].option;
        delete settingsOptions[i].displayedValue;
    }

    TTF_CloseFont(font);
    settingsOptions.clear();
    font = NULL;
    settingsConfirmButton = NULL;
}