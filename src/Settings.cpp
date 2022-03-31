#include "Settings.h"
#include "Vector2.h"

Settings::Settings(const App* p_system, bool& p_isOpened)
    :system(p_system), 
    renderer(p_system->getRenderer()),
    isOpened(p_isOpened)
{
    font = TTF_OpenFont("res/Staatliches-Regular.ttf", 35);
    selectedIdx = 0;
    isConfirmSelected = false;
    confirmButton = NULL;
    config = readSettingsConfig();

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
            STATUSES[config[i]] :
            SUPPORTED_LANGUAGES[ENGLISH],
            selectedIdx == i ? selectedOptionColor : textColor
        );

        SettingsOption option =
        {
            optionsTextTexture,
            valueTextTexture,
            config[i],
            type,
            type == LANGUAGE || i == FULLSCREEN_IDX, // isDisabled option (not supported now)
        };

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
        Texture* option = options[i].option;
        Texture* displayedValue = options[i].displayedValue;

        int offsetHeight = rect.y + offset;
        int offsetWidth = rect.x + margin / 2;

        // Hightlight selected option
        if (selectedIdx == i && !isConfirmSelected)
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

        option->render(Vector2(offsetWidth, offsetHeight));
        displayedValue->render(Vector2(rect.x + rect.w - displayedValue->getWidth() - margin / 2, offsetHeight));
    }
}

void Settings::updateSelectedOption(int nextIdx)
{
    // Hover out confirm button
    if (nextIdx != options.size() && isConfirmSelected)
    {
        confirmButton->loadFromRenderedText(
            font,
            CONFIRM_BUTTON_TEXT,
            textColor
        );

        isConfirmSelected = false;
    }
    else {
        // Hover out settings option
        SettingsOption selectedOption = options[selectedIdx];

        std::string optionText = selectedOption.type == SWITCHABLE ?
            STATUSES[selectedOption.value] :
            SUPPORTED_LANGUAGES[selectedOption.value];

        options[selectedIdx].displayedValue->loadFromRenderedText(
            font,
            optionText,
            textColor
        );
    }

    // Hover in confirm button selection
    if (nextIdx == options.size())
    {
        confirmButton->loadFromRenderedText(
            font,
            CONFIRM_BUTTON_TEXT,
            selectedOptionColor
        );

        isConfirmSelected = true;
    }
    else {
        // Hover out settings option
        SettingsOption nextOption = options[nextIdx];

        std::string optionText = nextOption.type == SWITCHABLE ?
            STATUSES[nextOption.value] :
            SUPPORTED_LANGUAGES[nextOption.value];

        // Hover in settings option
        options[nextIdx].displayedValue->loadFromRenderedText(
            font,
            optionText,
            nextOption.isDisabled ? selectedDisabledOptionColor : selectedOptionColor
        );
    }

    selectedIdx = nextIdx;
}

void Settings::updateValue()
{
    int nextValue;
    std::string nextTextValue;
    SettingsOption updatedOption = options[selectedIdx];

    if (updatedOption.isDisabled)
    {
        return;
    }

    if (updatedOption.type == LANGUAGE)
    {
        nextValue = updatedOption.value + 1 >= SUPPORTED_LANGUAGES.size() ? 0 : updatedOption.value + 1;
        nextTextValue = SUPPORTED_LANGUAGES[nextValue];
    }
    else {
        bool isDisabled = options[selectedIdx].value == DISABLED;
        nextValue = isDisabled ? ENABLED : DISABLED;
        nextTextValue = STATUSES[nextValue];

        bool isMuted;
        switch (selectedIdx)
        {
        case MUSIC_IDX:
            isMuted = system->getAudioPlayer()->isMusicMuted;
            system->getAudioPlayer()->setMuted(!isMuted);
            break;
        case SOUNDS_IDX:
            isMuted = system->getAudioPlayer()->isSoundsMuted;

            system->getAudioPlayer()->setMuted(!isMuted, false);
            break;
        }
    }

    config[selectedIdx] = nextValue;
    options[selectedIdx].value = nextValue;
    options[selectedIdx].displayedValue->loadFromRenderedText(
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

    int buttonWidth = confirmButton->getWidth();
    int buttonHeight = confirmButton->getHeight();
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
    if (!isOpened || e.type != SDL_KEYDOWN)
    {
        return;
    }

    char keyDown = e.key.keysym.scancode;

    if (keyDown == SDL_SCANCODE_RETURN)
    {
        if (isConfirmSelected)
        {
            close();
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
        if (selectedIdx - 1 >= 0)
        {
            updateSelectedOption(selectedIdx - 1);
        }
        break;
    case SDLK_DOWN:
    case SDLK_s:
        if (selectedIdx + 1 <= options.size())
        {
            updateSelectedOption(selectedIdx + 1);
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

    isOpened = false;
}

Settings::~Settings()
{
    delete confirmButton;

    for (int i = 0; i < options.size(); i++)
    {
        delete options[i].option;
        delete options[i].displayedValue;
    }

    TTF_CloseFont(font);
    options.clear();
    font = NULL;
    confirmButton = NULL;
}