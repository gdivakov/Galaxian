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