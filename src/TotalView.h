#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>

#include "Consts.h"
#include "Texture.h"
#include "LevelBase.h"

struct ShipUpgrade
{
	Texture* text;
	Texture* prevState;
	Texture* nextState;
	Texture* trasnformTo;
	int frame; // One frame instance as they have equal amount of sprite length
};

class TotalView // Todo: center ship previews
{
public:
	TotalView(LevelBase* p_level);
	~TotalView();

	bool getIsActive() { return isActive; };
	void setIsActive(bool nextIsActive) { initScore(); isActive = nextIsActive; };
	void onBeforeRender();
	void onAfterRender();
	void handleEvent(SDL_Event& e);
private:
	typedef std::map<std::string, Texture*> TextureMap;
	
	LevelBase* level;
	TTF_Font* font;
	TTF_Font* fontLarge;
	bool isActive = false;
	Texture* text;
	TextureMap scoreTextures;
	TextureMap buttonTextures;
	std::string selectedOption;
	ShipUpgrade shipUpgrade;

	void initScore();
	void initButtons();
};

