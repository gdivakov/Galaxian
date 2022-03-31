#include <iostream>

#include "Vector2.h"
#include "Background.h"
#include "Texture.h"

Background::Background(SDL_Renderer* p_renderer, std::string path, LevelBase* p_level, bool p_isDynamic)
	: Texture(p_renderer)
{
	isDynamic = p_isDynamic;
	loadFromFile(path);
	level = p_level;

	scrollingOffset = 0;
}

void Background::onBeforeRender()
{
	if (!isDynamic)
	{
		render(0, 0);
		return;
	}

	if (!level->isPaused)
	{
		scrollingOffset += 2;
	}
	
	if (scrollingOffset > getHeight())
	{
		scrollingOffset = 0;
	}

	render(Vector2(0, scrollingOffset));
	render(Vector2(0, scrollingOffset - getHeight()));
}

void Background::onAfterRender()
{}

void Background::handleEvent(SDL_Event& e)
{}