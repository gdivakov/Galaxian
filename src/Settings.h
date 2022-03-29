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
	SDL_Renderer* renderer;
	const App* system;
	TTF_Font* font;
	std::vector<SettingsOption> settingsOptions;
	int selectedSettingsIdx;
	bool isSettingsConfirmSelected;
	Texture* settingsConfirmButton;
	bool& isOpened;
	std::vector<int> config;
public: 
	Settings(const App* p_system, bool& p_isOpened);
	~Settings();
	void loadOptions();
	void render();
	void updateSelectedOption(int nextIdx);
	void updateValue();
	void renderConfirm();

	virtual void handleRender();
	virtual void handleEvent(SDL_Event& e);
};

