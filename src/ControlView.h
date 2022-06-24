#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>

#include "LevelBase.h"
#include "Consts.h"
#include "Texture.h"

struct ControlRow
{
	Texture* leftImage;
	Texture* text;
	Texture* rightImage;
};

class ControlView
{
public:
	ControlView(LevelBase* p_level, bool& p_isActive);
	~ControlView();

	void handleRender();
	void handleEvent(SDL_Event& e);
private:
	LevelBase* level;
	bool& isActive;
	TTF_Font* font;
	Texture* catTexture;
	std::vector<ControlRow> rows;

	void initRows();
};

