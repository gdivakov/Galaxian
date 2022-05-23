#pragma once
#include <SDL.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "LevelBase.h"

class GameOverView
{
public:
	GameOverView(LevelBase* level);
	~GameOverView();
	void handleRender();
	void handleEvent(SDL_Event& e);
	bool getIsActive() { return isActive; };
	void setIsActive(bool nextIsActive) { isActive = nextIsActive; };
private:
	Texture* texture;
	Texture* tooltipTexture;
	LevelBase* level;
	TTF_Font* font;
	TTF_Font* smallFont;
	int bottomShift;
	int maxShift;

	bool isActive;
};

