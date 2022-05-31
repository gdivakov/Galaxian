#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "Texture.h"
#include "App.h"
#include "MainScreen.h"
#include "PanelConsts.h"
#include "Consts.h"
#include "Settings.h"

class MainScreen;

class ControlPanel : public Object
{
private:
	SDL_Renderer* renderer;
	const App* system;
	std::vector<Texture*> options;
	TTF_Font* font;
	TTF_Font* smallFont;
	int selectedOptionIdx;
	Texture* tooltip;
	MainScreen* mainScreenPt;
	bool isSettingsOpened;
	Settings* settingsView;
	bool isActive;
public:
	ControlPanel(SDL_Renderer* p_renderer, const App* p_system, MainScreen* p_mainScreenPt);
	~ControlPanel();
	void loadOptions();
	void renderOptions();
	void updateSelectedOption(int nextIdx);
	void setIsActive(bool nextIsActive) { isActive = nextIsActive; };

	virtual void onBeforeRender();
	virtual void onAfterRender() {};
	virtual void handleEvent(SDL_Event& e);
};

