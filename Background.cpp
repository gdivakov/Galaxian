#include "Background.h"
#include "Texture.h"

Background::Background(SDL_Renderer* p_renderer, std::string path) : Texture(p_renderer)
{
	loadFromFile(path);
	scrollingOffset = 0;
}

Background::~Background()
{}

void Background::onBeforeRender()
{
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

void Background::handleEvent()
{}