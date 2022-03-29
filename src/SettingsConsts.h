#pragma once
#include <SDL.h>
#include "Texture.h"
#include <vector>

const std::vector<std::string> NAMES = {
    "Music",
    "Sounds",
    "Fullscreen mode",
    "Language",
};

const std::vector<std::string> STATUSES = {
    "Disabled",
    "Enabled"
};

const std::vector<std::string> SUPPORTED_LANGUAGES = {
    "English",
    "Russian"
};

const std::string CONFIRM_BUTTON_TEXT = "Save";

const enum SettingsIndexes { MUSIC_IDX, SOUNDS_IDX, FULLSCREEN_IDX, LANGUAGE_IDX };
const enum OptionStatus { DISABLED, ENABLED };
const enum SupportedLanguages { ENGLISH, RUSSIAN };
const enum OptionType { LANGUAGE, SWITCHABLE };

struct SettingsOption
{
    Texture* option;
    Texture* displayedValue;
    int value;
    OptionType type;
    bool isDisabled;
};

const std::string SETTINGS_CONFIG_PATH = "res/store/settings.bin";
const std::vector<int> DEFAULT_SETTINGS_CONFIG = { 1, 1, 0, 0 };

static void writeSettingsConfig(std::vector<int> source = DEFAULT_SETTINGS_CONFIG)
{
    SDL_RWops* file = SDL_RWFromFile(SETTINGS_CONFIG_PATH.c_str(), "w+b");

    if (file == NULL)
    {
        std::cout << "Write settings config error: " << SDL_GetError() << std::endl;
        return;
    }

    for (int i = 0; i < source.size(); i++)
    {
        SDL_RWwrite(file, &source[i], sizeof(int), 1);
    }

    SDL_RWclose(file);
}

static std::vector<int> readSettingsConfig()
{
    std::vector<int> config(DEFAULT_SETTINGS_CONFIG.size());

    SDL_RWops* file = SDL_RWFromFile(SETTINGS_CONFIG_PATH.c_str(), "r+b");

    if (file == NULL)
    {
        // Create new config file and set default values
        std::cout << "Create new settings config." << std::endl;

        file = SDL_RWFromFile(SETTINGS_CONFIG_PATH.c_str(), "w+b");

        if (file == NULL)
        {
            SDL_RWclose(file);
            std::cout << "Creation file error: " << SDL_GetError() << std::endl;
            return DEFAULT_SETTINGS_CONFIG;
        }

        std::cout << "New settings config created." << std::endl;

        SDL_RWclose(file);

        writeSettingsConfig();

        return DEFAULT_SETTINGS_CONFIG;
    }

    for (int i = 0; i < config.size(); i++)
    {
        SDL_RWread(file, &config[i], sizeof(int), 1);
    }

    SDL_RWclose(file);

    return config;
}