#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "Texture.h"
#include "App.h"
#include "MainScreen.h"
#include "PanelConsts.h"

class ControlPanel : public Object
{
private:
	SDL_Renderer* renderer;
	const App* system;
	std::vector<Texture*> options;
	std::vector<SettingsOption> settingsOptions;
	TTF_Font* font;
	TTF_Font* smallFont;
	int selectedOptionIdx;
	int selectedSettingsIdx;
	bool isSettingsOpened;
	bool isSettingsConfirmSelected;
	Texture* settingsConfirmButton;
	Texture* tooltip;
	MainScreen* mainScreenPt;
public:
	ControlPanel(SDL_Renderer* p_renderer, const App* p_system, MainScreen* p_mainScreenPt);
	~ControlPanel();
	void loadOptions();
	void loadSettingsOptions();
	void renderOptions();
	void renderSettings();
	void updateSelectedOption(int nextIdx);
	void updateSelectedSettingsOption(int nextIdx);
	void updateSettingValue();
	void renderSettingsConfirm();
	int getSettingOptionValue(int idx, OptionType type);
	virtual void onBeforeRender();
	virtual void onAfterRender() {};
	virtual void handleEvent(SDL_Event& e);
};

