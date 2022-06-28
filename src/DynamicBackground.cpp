#include <iostream>

#include "DynamicBackground.h"
#include "Vector2.h"
#include "SpecialsConsts.h"

DynamicBackground::DynamicBackground(SDL_Renderer* p_renderer, std::string path, LevelBase* p_level)
	: Texture(p_renderer)
{
	loadFromFile(path);
	level = p_level;

	scrollingSpeed = BG_SCROLLING_SPEED;
	scrollingOffset = 0;
}

DynamicBackground::~DynamicBackground()
{
	level = nullptr;
}

void DynamicBackground::onBeforeRender()
{
	if (!level->isPaused)
	{
		int speed = scrollingSpeed;

		if (level->getIsAccelerated())
		{
			speed = BG_SCROLLING_SPEED_ACCELERATED;
		}
		else if (level->getIsCompleted())
		{
			speed = 0;
		}

		scrollingOffset += speed;
	}

	if (scrollingOffset > getHeight())
	{
		scrollingOffset = 0;
	}

	render(Vector2(0, scrollingOffset));
	render(Vector2(0, scrollingOffset - getHeight()));
}