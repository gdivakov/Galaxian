#include "ControlPanel.h"

// Todo: simplify here: move settings view to another class, create utils file
ControlPanel::ControlPanel(SDL_Renderer* p_renderer, const App* p_system, MainScreen* p_mainScreenPt)
{
    renderer = p_renderer;
    system = p_system;
    mainScreenPt = p_mainScreenPt;
    font = TTF_OpenFont("res/Staatliches-Regular.ttf", 35);
    smallFont = TTF_OpenFont("res/Staatliches-Regular.ttf", 20);
    selectedOptionIdx = START_GAME;
    selectedSettingsIdx = 0;
    isSettingsOpened = false;
    isSettingsConfirmSelected = false;
    settingsConfirmButton = NULL;
    
    loadOptions();
    loadSettingsOptions();
}

void ControlPanel::onBeforeRender()
{
    if (isSettingsOpened)
    {
        renderSettings();
        renderSettingsConfirm();
    }
    else {
        // Reset selected option when settings is closed
        if (selectedSettingsIdx != 0)
        {
            updateSelectedSettingsOption(0);
        }
        renderOptions();
    }
}

void ControlPanel::renderSettingsConfirm()
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

void ControlPanel::renderSettings()
{
    // Render settings panel
    SDL_Rect rect = { 
        WINDOWED_WIDTH/14, 
        WINDOWED_HEIGHT/14, 
        WINDOWED_WIDTH - WINDOWED_WIDTH / 7, 
        WINDOWED_HEIGHT - WINDOWED_HEIGHT / 7 
    };

    SDL_SetRenderDrawColor(renderer, 0x01, 0x62, 0xb1, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &rect);

    // Render options
    SDL_Point selectedOptionPos;
    int margin = rect.h / (SETTINGS_OPTION_NAMES.size() + 1);

    for (int i = 0, offset = margin/3; i < SETTINGS_OPTION_NAMES.size(); i++, offset += margin)
    {
        Texture* option = settingsOptions[i].option;
        Texture* displayedValue = settingsOptions[i].displayedValue;
        
        int offsetHeight = rect.y + offset;
        int offsetWidth = rect.x + margin/2;

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

void ControlPanel::renderOptions()
{
    for (int i = 0, offset = 10; i < MENU_OPTION_NAMES.size(); i++, offset += 40)
    {
        Texture* option = options[i];

        int offsetHeight = (WINDOWED_HEIGHT - (option->getHeight() * 3)) / 2;
        int offsetWidth = (WINDOWED_WIDTH - option->getWidth()) / 2 + 200;

        // Hightlight selected option
        if (selectedOptionIdx == i)
        {
            SDL_Point selectedOptionPos = { offsetWidth, offsetHeight + offset };

            SDL_Rect rect = {
                selectedOptionPos.x - 5,
                selectedOptionPos.y,
                options[i]->getWidth() + 10,
                options[i]->getHeight() - 3,
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }

        option->render(offsetWidth, offsetHeight + offset);
    }

    // Render tooltip
    tooltip->render(
        (WINDOWED_WIDTH - tooltip->getWidth())/2, 
        WINDOWED_HEIGHT - tooltip->getHeight() - 16
    );
}

void ControlPanel::handleEvent(SDL_Event& e) // Todo: separate by functions 
{
    if (e.type == SDL_KEYDOWN)
    {
        char keyDown = e.key.keysym.scancode;

        if (keyDown == SDL_SCANCODE_RETURN)
        {
            if (isSettingsOpened) {
                if (isSettingsConfirmSelected)
                {
                    isSettingsOpened = false;
                }
                else {
                    updateSettingValue();
                }
            } else {
                if (selectedOptionIdx == START_GAME)
                {
                    mainScreenPt->startGame();
                    return;
                }

                if (selectedOptionIdx == SETTINGS)
                {
                    isSettingsOpened = true;
                }

                if (selectedOptionIdx == QUIT)
                {

                    mainScreenPt->quit();
                    return;
                }
            }
        }

        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            case SDLK_w:
                if (isSettingsOpened && selectedSettingsIdx - 1 >= 0)
                {
                    int nextSelectedSettingsIdx = selectedSettingsIdx - 1;
                    updateSelectedSettingsOption(nextSelectedSettingsIdx);
                }

                if (!isSettingsOpened)
                {
                    int nextSelectedOptionIdx = selectedOptionIdx - 1 < 0 ? options.size() - 1 : selectedOptionIdx - 1;
                    updateSelectedOption(nextSelectedOptionIdx);
                }
                break;
            case SDLK_DOWN:
            case SDLK_s:
                if (isSettingsOpened && selectedSettingsIdx + 1 <= settingsOptions.size() )
                {
                    int nextSelectedSettingsIdx = selectedSettingsIdx + 1;
                    updateSelectedSettingsOption(nextSelectedSettingsIdx);
                } 
                
                if (!isSettingsOpened)
                {
                    int nextSelectedOptionIdx = selectedOptionIdx + 1 > options.size() - 1 ? 0 : selectedOptionIdx + 1;
                    updateSelectedOption(nextSelectedOptionIdx);
                }
                break;
        }
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

void ControlPanel::loadSettingsOptions()
{
    for (int i = 0; i < SETTINGS_OPTION_NAMES.size(); i++)
    {
        Texture* optionsTextTexture = new Texture(renderer);
        Texture* valueTextTexture = new Texture(renderer);
        OptionType type = i != LANGUAGE_IDX ? SWITCHABLE : LANGUAGE;

        optionsTextTexture->loadFromRenderedText(
            font,
            SETTINGS_OPTION_NAMES[i],
            textColor
        );

        valueTextTexture->loadFromRenderedText(
            font,
            type == SWITCHABLE ?
                SETTINGS_OPTION_STATUSES[getSettingOptionValue(i, type)] :
                SETTINGS_OPTION_SUPPORTED_LANGUAGES[ENGLISH], 
            selectedSettingsIdx == i ? selectedOptionColor : textColor
        );

        SettingsOption option =
        {
            optionsTextTexture,
            valueTextTexture,
            type == getSettingOptionValue(i, type),
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

void ControlPanel::updateSelectedSettingsOption(int nextIdx)
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
            SETTINGS_OPTION_STATUSES[selectedOption.value] :
            SETTINGS_OPTION_SUPPORTED_LANGUAGES[selectedOption.value];

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
    } else {
        // Hover out settings option
        SettingsOption nextOption = settingsOptions[nextIdx];

        std::string optionText = nextOption.type == SWITCHABLE ?
            SETTINGS_OPTION_STATUSES[nextOption.value] :
            SETTINGS_OPTION_SUPPORTED_LANGUAGES[nextOption.value];

        // Hover in settings option
        settingsOptions[nextIdx].displayedValue->loadFromRenderedText(
            font,
            optionText,
            nextOption.isDisabled ? selectedDisabledOptionColor : selectedOptionColor
        );
    }

    selectedSettingsIdx = nextIdx;
}

void ControlPanel::updateSettingValue() // Todo: save on disk
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
        int nextLanguageIdx = updatedOption.value + 1 >= SETTINGS_OPTION_SUPPORTED_LANGUAGES.size() ? 0 : updatedOption.value + 1;
        nextValue = SupportedLanguages (nextLanguageIdx);
        nextTextValue = SETTINGS_OPTION_SUPPORTED_LANGUAGES[nextValue];
    } else {
        bool isDisabled = settingsOptions[selectedSettingsIdx].value == DISABLED;
        nextValue = isDisabled ? ENABLED : DISABLED;
        nextTextValue = SETTINGS_OPTION_STATUSES[nextValue];

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

int ControlPanel::getSettingOptionValue(int idx, OptionType type)
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

ControlPanel::~ControlPanel()
{
    delete settingsConfirmButton;
    delete tooltip;

    for (int i = 0; i < options.size(); i++)
    {
        delete options[i];
    }

    for (int i = 0; i < settingsOptions.size(); i++)
    {
        delete settingsOptions[i].option;
        delete settingsOptions[i].displayedValue;
    }

    options.clear();
    settingsOptions.clear();
    TTF_CloseFont(font);
    TTF_CloseFont(smallFont);
    settingsConfirmButton = NULL;
    tooltip = NULL;
    font = NULL;
    smallFont = NULL;
    renderer = NULL;
}