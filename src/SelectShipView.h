#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Texture.h"
#include "Object.h"
#include "LevelBase.h"

class Ship;

struct ShipPreview 
{
	int frame;
	Texture* sprite;
};

class SelectShipView : public Object
{
public:
	SelectShipView(LevelBase* p_level);
	~SelectShipView();
	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent(SDL_Event& e);

	bool getIsShipSelected() { return isShipSelected; };
	void show();
private:
	LevelBase* level;
	std::vector<ShipPreview> ships;
	Texture* text;
	TTF_Font* font;
	bool isActive;
	int selectedShipIdx;
	bool isShipSelected;
};

