#pragma once

#include <vector>
#include <iostream>
#include <SDL.h>

const std::vector<std::string> MENU_OPTION_NAMES = {
    "Start game",
    "Settings",
    "Quit",
};

const std::string TOOLTIP_TEXT = "Use arrows and Enter to navigate";

const enum MenuOption { MENU_START_GAME, MENU_SETTINGS, MENU_QUIT };