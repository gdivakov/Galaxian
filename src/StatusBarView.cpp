#include <iostream>

#include "StatusBarView.h"
#include "App.h"
#include "Ship.h"

const int STATUS_BAR_WIDTH = 120;
const int STATUS_BAR_HEIGHT = 15;

const std::string TEXTURE_PATH_STATUSBAR_HEALTH = "res/icons/health.png";
const std::string TEXTURE_PATH_STATUSBAR_ARMOR = "res/icons/armor.png";

StatusBarView::StatusBarView(LevelBase* p_level)
{
	level = p_level;

	health = new Texture(level->getSystem()->getRenderer());
	health->loadFromFile(TEXTURE_PATH_STATUSBAR_HEALTH);

	armor = new Texture(level->getSystem()->getRenderer());
	armor->loadFromFile(TEXTURE_PATH_STATUSBAR_ARMOR);
}

StatusBarView::~StatusBarView()
{
	delete health;
	delete armor;

	health = NULL;
	armor = NULL;
	level = NULL;
}

void StatusBarView::handleRender()
{
	Ship* player = level->getPlayer();

	if (!player)
	{
		return;
	}

	const App* system = level->getSystem();
	SDL_Renderer* renderer = system->getRenderer();
	const Size* windowSize = system->getWindowSize();

	StatusModule* statusModule = level->getPlayer()->getSpecials()->status;

	float healthBarValue = player ? statusModule->getHealth() / (float)statusModule->getMaxHealth() : 0;
	float armorBarValue = player ? statusModule->getArmor() / (float)statusModule->getMaxArmor() : 0;

	SDL_Rect armorBar = 
	{ 
		windowSize->w - STATUS_BAR_WIDTH - 16, 
		windowSize->h - STATUS_BAR_HEIGHT * 2 - 24, 
		STATUS_BAR_WIDTH,
		STATUS_BAR_HEIGHT
	};

	SDL_Rect healthBar =
	{
		windowSize->w - STATUS_BAR_WIDTH - 16,
		windowSize->h - STATUS_BAR_HEIGHT - 16,
		STATUS_BAR_WIDTH,
		STATUS_BAR_HEIGHT
	};

	healthBar.w *= healthBarValue;
	armorBar.w *= armorBarValue;

	SDL_SetRenderDrawColor(renderer, 0xF7, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &healthBar);

	SDL_SetRenderDrawColor(renderer, 0xa1, 0xa1, 0xa1, 0xFF);
	SDL_RenderFillRect(renderer, &armorBar);
	
	SDL_SetRenderDrawColor(renderer, 0xa1, 0xa1, 0xa1, 0xFF);

	if (healthBar.w)
	{
		SDL_RenderDrawRect(renderer, &healthBar);
		health->render(Vector2(healthBar.x - health->size.w - 8, healthBar.y - (health->size.h - STATUS_BAR_HEIGHT) / 2));
	}

	if (armorBar.w)
	{
		SDL_RenderDrawRect(renderer, &armorBar);
		armor->render(Vector2(armorBar.x - health->size.w - 8, armorBar.y - (armor->size.h - STATUS_BAR_HEIGHT) / 2));
	}
}

