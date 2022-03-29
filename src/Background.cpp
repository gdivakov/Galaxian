#include "Background.h"
#include "Texture.h"
#include <iostream>

Background::Background(SDL_Renderer* p_renderer, std::string path, bool p_isDynamic) : Texture(p_renderer) // Todo: set diff modes (static and scrolled)
{
	isDynamic = p_isDynamic;
	loadFromFile(path);

	scrollingOffset = 0;
}

void Background::onBeforeRender()
{
	if (!isDynamic)
	{
		render(0, 0);
		return;
	}

	scrollingOffset += 2;
	if (scrollingOffset > getHeight())
	{
		scrollingOffset = 0;
	}

	render(0, scrollingOffset);
	render(0, scrollingOffset - getHeight());
}

void Background::onAfterRender()
{}

void Background::handleEvent(SDL_Event& e)
{}