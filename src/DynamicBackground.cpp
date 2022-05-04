#include <iostream>

#include "DynamicBackground.h"
#include "Vector2.h"

DynamicBackground::DynamicBackground(SDL_Renderer* p_renderer, std::string path, LevelBase* p_level)
	: Texture(p_renderer)
{
	loadFromFile(path);
	level = p_level;

	scrollingOffset = 0;
}

void DynamicBackground::onBeforeRender()
{
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