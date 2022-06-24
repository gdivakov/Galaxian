#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <vector>

#include "App.h"
#include "Texture.h"
#include "SettingsConsts.h"
#include "Consts.h"

class Settings
{
public:
	Settings(const App* p_system, bool& p_isActive);
	~Settings();
	void loadOptions();
	void render();
	void updateSelectedOption(int nextIdx);
	void updateValue();
	void renderConfirm();

	void handleRender();
	void handleEvent(SDL_Event& e);
private:
	SDL_Renderer* renderer;
	const App* system;
	TTF_Font* font;
	std::vector<SETTINGS_FIELDS::SettingsOption> options;
	int selectedIdx;
	bool isConfirmSelected;
	Texture* confirmButton;
	bool& isActive;
	std::vector<int> config;

	void close();
};

