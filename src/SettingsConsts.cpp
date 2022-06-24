#include "SettingsConsts.h"

using namespace SETTINGS_FIELDS;

std::vector<std::string> SETTINGS_FIELDS::getAvailableValues(Types type) {
    switch (type)
    {
    case DIFFICULTY:
        return { "easy", "hard" };
    case LANGUAGE:
        return { "english", "ukrainian" };
    default:
        return { "disabled", "enabled" };
    }
}