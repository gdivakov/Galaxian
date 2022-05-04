#pragma once
#include <SDL.h>
#include <vector>
#include <SDL_ttf.h>

#include "Texture.h"
#include "LevelBase.h"
#include "Settings.h"
#include "App.h"
#include "Hood.h"
#include "Object.h"

class Hood;

class PauseView : public Object
{
public:
	PauseView(LevelBase* p_level, Hood* p_hood);
	~PauseView();
	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
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
	Hood* parentHood;
};