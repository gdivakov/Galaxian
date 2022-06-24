#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "LevelBase.h"
#include "Consts.h"

struct DescRow
{
	Texture* image;
	Texture* text;
};

class BuffDescView
{
public:
	BuffDescView(LevelBase* p_level, bool& p_isActive);
	~BuffDescView();

	void handleRender();
	void handleEvent(SDL_Event& e);
private:
	LevelBase* level;
	bool& isActive;
	std::vector<DescRow> rows;
	TTF_Font* font;
	TTF_Font* fontTitle;

	Texture* title;

	void initRows();
};

