#include "PauseView.h"
#include "Consts.h"
#include "Vector2.h"

std::vector<std::string> PAUSE_MENU_NAMES = 
{
    "Resume",
    "Settings",
    "Quit"
};

const enum PAUSE_OPTION_IDX { RESUME_IDX, SETTINGS_IDX, QUIT_IDX };

// Todo: fix music mute
PauseView::PauseView(const App* p_system, LevelBase* p_level)
    : renderer(p_system->getRenderer()), level(p_level), system(p_system)
{
    font = TTF_OpenFont("res/Staatliches-Regular.ttf", 35);
    selectedIdx = RESUME_IDX;
    isSettingsOpened = false;

    settingsView = new Settings(system, isSettingsOpened);

    loadOptions();
}

void PauseView::handleRender()
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
    int margin = rect.h / (PAUSE_MENU_NAMES.size() + 3);

    for (int i = 0, offset = margin * 2; i < PAUSE_MENU_NAMES.size(); i++, offset += margin)
    {
        Texture* option = options[i];
        std::string displayedValue = PAUSE_MENU_NAMES[i];

        int offsetHeight = rect.y + offset;
        int offsetWidth = rect.x + (rect.w - option->getWidth()) / 2;

        // Hightlight selected option
        if (selectedIdx == i)
        {
            SDL_Rect rect = {
                offsetWidth - 5,
                offsetHeight,
                option->getWidth() + 10,
                option->getHeight() - 3,
            };

            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &rect);
        }

        option->render(Vector2(offsetWidth, offsetHeight));
    }

    if (isSettingsOpened)
    {
        settingsView->handleRender();
    }
}
	
void PauseView::handleEvent(SDL_Event& e)
{
    if (isSettingsOpened)
    {
        settingsView->handleEvent(e);
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
        }
        return;
    case SDLK_DOWN:
    case SDLK_s:
        if (selectedIdx + 1 < options.size())
        {
            updateSelectedOption(selectedIdx + 1);
        }
        return;
    }

    char keyDown = e.key.keysym.scancode;

    if (keyDown == SDL_SCANCODE_RETURN)
    {
        if (selectedIdx == RESUME_IDX)
        {
            bool isPaused = level->togglePaused();
            system->getAudioPlayer()->togglePaused(isPaused);
            return;
        }

        if (selectedIdx == SETTINGS_IDX)
        {
            isSettingsOpened = true;
        }

        if (selectedIdx == QUIT_IDX)
        {
            level->quit();
            return;
        }
    }
}

void PauseView::loadOptions()
{
    for (int i = 0; i < PAUSE_MENU_NAMES.size(); i++)
    {
        Texture* optionsTextTexture = new Texture(renderer);

        optionsTextTexture->loadFromRenderedText(
            font,
            PAUSE_MENU_NAMES[i],
            i == RESUME_IDX ? selectedOptionColor : textColor
        );

        options.push_back(optionsTextTexture);
    }
}

void PauseView::updateSelectedOption(int nextIdx)
{
    Texture* selectedOption = options[selectedIdx];
    Texture* nextSelectedOption = options[nextIdx];
    std::string optionText = PAUSE_MENU_NAMES[selectedIdx];
    std::string nextOptionText = PAUSE_MENU_NAMES[nextIdx];

    options[selectedIdx]->loadFromRenderedText(
        font,
        optionText,
        textColor
    );

    options[nextIdx]->loadFromRenderedText(
        font,
        nextOptionText,
        selectedOptionColor
    );

    selectedIdx = nextIdx;
}

PauseView::~PauseView()
{
    for (int i = 0; i < options.size(); i++)
    {
        delete options[i];
    }

    TTF_CloseFont(font);
    options.clear();
    font = NULL;
    level = NULL;
}