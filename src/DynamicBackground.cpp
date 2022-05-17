#include <iostream>

#include "DynamicBackground.h"
#include "Vector2.h"
#include "ShipSpecialsConsts.h"

DynamicBackground::DynamicBackground(SDL_Renderer* p_renderer, std::string path, LevelBase* p_level)
	: Texture(p_renderer)
{
	loadFromFile(path);
	level = p_level;

	scrollingSpeed = BG_SCROLLING_SPEED;
	scrollingOffset = 0;
}

void DynamicBackground::onBeforeRender()
{
	if (!level->isPaused)
	{
		updateAcceleratedStatus();

		int speed = isAccelerated ? BG_SCROLLING_SPEED_ACCELERATED : scrollingSpeed;
		scrollingOffset += speed;
	}

	if (scrollingOffset > getHeight())
	{
		scrollingOffset = 0;
	}

	render(Vector2(0, scrollingOffset));
	render(Vector2(0, scrollingOffset - getHeight()));
}

void DynamicBackground::accelerate()
{
	isAccelerated = true;
	acceleratedAt = level->getSystem()->getTimer()->getTicks();
}

void DynamicBackground::updateAcceleratedStatus()
{
	if (!isAccelerated)
	{
		return;
	}

	Uint32 currentTime = level->getSystem()->getTimer()->getTicks();
	BuffParams params = getBuffParamsByType(BUFF_SPEED_UP);

	if (currentTime - acceleratedAt > params.duration)
	{
		isAccelerated = false;
	}
}