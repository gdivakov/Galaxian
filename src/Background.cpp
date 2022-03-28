#include "Background.h"
#include "Texture.h"
#include <iostream>

Background::Background(SDL_Renderer* p_renderer, std::string path, Type p_mode) : Texture(p_renderer) // Todo: set diff modes (static and scrolled)
{
	mode = p_mode;
	loadFromFile(path);

	scrollingOffset = 0;
}

void Background::onBeforeRender()
{
	if (mode != DYNAMIC)
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