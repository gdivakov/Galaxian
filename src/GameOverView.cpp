#include <iostream>

#include "GameOverView.h"
#include "Consts.h"

const std::string GAME_OVER_TEXT = "Game Over";
const std::string TOOLTIP_TEXT = "Press ENTER to restart or ESC to quit.";

GameOverView::GameOverView(LevelBase* p_level)
{
	level = p_level;
	font = TTF_OpenFont(FONT_PATH.c_str(), DEFAULT_FONT_SIZE);
	smallFont = TTF_OpenFont(FONT_PATH.c_str(), SMALL_FONT_SIZE);

	texture = new Texture(level->getSystem()->getRenderer());
	texture->loadFromRenderedText(font, GAME_OVER_TEXT, selectedOptionColor);

	tooltipTexture = new Texture(level->getSystem()->getRenderer());
	tooltipTexture->loadFromRenderedText(smallFont, TOOLTIP_TEXT, selectedOptionColor);

	bottomShift = 0;
	isActive = false;

	maxShift = (level->getSystem()->getWindowSize()->h - (texture->size.h + tooltipTexture->size.h + 32)) / 2;
}

GameOverView::~GameOverView()
{
	delete texture;
	delete tooltipTexture;

	TTF_CloseFont(font);
	TTF_CloseFont(smallFont);

	texture = NULL;
	tooltipTexture = NULL;
	level = NULL;
	font = NULL;
	smallFont = NULL;
}

void GameOverView::handleRender()
{
	if (!isActive)
	{
		return;
	}

	const Size* windowSize = level->getSystem()->getWindowSize();

	Vector2 texturePos((windowSize->w - texture->size.w)/2, windowSize->h - texture->size.h - tooltipTexture->size.h - 16*2 - bottomShift);
	Vector2 tooltipPos((windowSize->w - tooltipTexture->size.w) / 2, windowSize->h - tooltipTexture->size.h - 16 - bottomShift);

	texture->render(texturePos);
	tooltipTexture->render(tooltipPos);

	if (bottomShift <= maxShift)
	{	
		bottomShift += 5;
	}
}

void GameOverView::handleEvent(SDL_Event& e)
{
	if (!isActive || e.type != SDL_KEYDOWN)
	{
		return;
	}

	switch (e.key.keysym.scancode)
	{
	case SDL_SCANCODE_RETURN:
		level->restart();
		break;
	case SDL_SCANCODE_ESCAPE:
		break;
	}
}