#pragma once

#include <vector>
#include <iostream>
#include <SDL.h>

#include "Texture.h"

const enum OptionType { LANGUAGE, SWITCHABLE };

struct SettingsOption
{
	Texture* option;
	Texture* displayedValue;
	int value;
	OptionType type;
	bool isDisabled;
};

const std::vector<std::string> MENU_OPTION_NAMES = {
    "Start game",
    "Settings",
    "Quit",
};

const std::vector<std::string> SETTINGS_OPTION_NAMES = {
    "Music",
    "Sounds",
    "Fullscreen mode",
    "Language",
};

const std::vector<std::string> SETTINGS_OPTION_STATUSES = {
    "Disabled",
    "Enabled"
};

const std::vector<std::string> SETTINGS_OPTION_SUPPORTED_LANGUAGES = {
    "English",
    "Russian"
};

const std::string CONFIRM_BUTTON_TEXT = "Save";
const std::string TOOLTIP_TEXT = "Use arrows and Enter to navigate";

const enum MenuOption { START_GAME, SETTINGS, QUIT };
const enum SettingsIndexes { MUSIC_IDX, SOUNDS_IDX, FULLSCREEN_IDX, LANGUAGE_IDX };
const enum OptionStatus { DISABLED, ENABLED };
const enum SupportedLanguages { ENGLISH, RUSSIAN };

const SDL_Color textColor = { 0, 0, 0 };
const SDL_Color selectedOptionColor = { 1, 98, 177 };
const SDL_Color selectedDisabledOptionColor = { 153, 153, 153 };