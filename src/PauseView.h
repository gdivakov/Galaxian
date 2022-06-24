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
#include "ControlView.h"
#include "BuffDescView.h"

class Hood;
class ControlView;
class BuffDescView;

namespace PAUSE_FIELDS
{
	const enum Types { RESUME, SETTINGS, CONTROL, BUFF_DESCRIPTION, QUIT };

	const std::map<Types, const std::string> NAMES =
	{
		{ RESUME, "Resume" },
		{ SETTINGS, "Settings" },
		{ CONTROL, "Control" },
		{ BUFF_DESCRIPTION, "Buff  desc" },
		{ QUIT, "Quit" },
	};

	struct PauseOption
	{
		Texture* optionTexture;
		Types fieldType;
	};
}

class PauseView : public Object
{
public:
	PauseView(LevelBase* p_level, Hood* p_hood);
	~PauseView();

	bool hasNestedActive() { return isSettingsActive || isControlActive || isBuffDescActive; };
	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
private:
	const App* system;
	SDL_Renderer* renderer;
	LevelBase* level;
	Hood* parentHood;

	bool isSettingsActive;
	bool isControlActive;
	bool isBuffDescActive;
	int selectedIdx;
	std::vector<PAUSE_FIELDS::PauseOption> options;
	TTF_Font* font;
	Settings* settingsView;
	ControlView* controlView;
	BuffDescView* buffDescView;

	void loadOptions();
	void updateSelectedOption(int nextIdx);
};