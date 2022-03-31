#pragma once
#include <SDL.h>
#include <vector>
#include <SDL_ttf.h>

#include "Texture.h"
#include "LevelBase.h"
#include "Settings.h"
#include "App.h"

// Todo: show score top right
// Todo: show controlling
// Todo: disable react to holding esc and arrows buttons
class PauseView
{
public:
	PauseView(const App* p_system, LevelBase* p_level);
	~PauseView();
	void handleRender();
	void handleEvent(SDL_Event& e);
	bool isSettingsOpened;
private:
	SDL_Renderer* renderer;
	std::vector<Texture*> options;
	TTF_Font* font;
	int selectedIdx;
	void loadOptions();
	void updateSelectedOption(int nextIdx);
	LevelBase* level;
	Settings* settingsView;
	const App* system;
};