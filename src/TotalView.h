#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>

#include "Consts.h"
#include "Texture.h"
#include "LevelBase.h"

class TotalView
{
public:
	TotalView(LevelBase* p_level);
	~TotalView();

	void handleRender();
	void handleEvent(SDL_Event& e);
	bool getIsActive() { return isActive; };
	void setIsActive(bool nextIsActive) { initScore(); isActive = nextIsActive; };
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

	void initScore();
	void initButtons();
};

