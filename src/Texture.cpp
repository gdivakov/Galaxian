#include <SDL.h>
#include <iostream>

#include "Texture.h"
#include "Consts.h"

struct RGB {
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

Texture::Texture(SDL_Renderer* p_renderer)
{
	renderer = p_renderer;
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(std::string path, RGB* colorKeyRGB)
{
	using std::cout;
	using std::endl;

	free();
	SDL_Texture* preparedTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		cout << "Unable to load image %s! SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}

	if (colorKeyRGB != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(
			loadedSurface->format,
			colorKeyRGB->r,
			colorKeyRGB->g,
			colorKeyRGB->b
		));
	}

	preparedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	if (preparedTexture == NULL)
	{
		cout << "Unable to create texture from: " 
			<< path.c_str() << endl 
			<< "Error: " 
			<< SDL_GetError() << endl;

		return false;
	}

	width = loadedSurface->w;
	height = loadedSurface->h;
	texture = preparedTexture;

	SDL_FreeSurface(loadedSurface);

	return texture != NULL;
}

void Texture::render(
	int x, 
	int y, 
	SDL_Rect* clip, 
	double angle, 
	SDL_Point* center, 
	SDL_RendererFlip flip
)
{
	SDL_Rect renderQuad = { x, y, width, height };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

bool Texture::loadFromSprite(std::string path, SpriteParams params, RGB* colorKeyRGB)
{
	if (!loadFromFile(path, colorKeyRGB))
	{
		return false;
	}

	for (int i = 0; i < params.length; i++)
	{
		SDL_Rect nextImage = { params.imageW * i, 0, params.imageW, params.imageH };
		spriteClips.push_back(nextImage);
	}

	return true;
}

Texture::Clips& Texture::getClips()
{
	return spriteClips;
}

void Texture::free()
{
	if (texture == NULL)
	{
		return;
	}

	SDL_DestroyTexture(texture);
	texture = NULL;
	renderer = NULL;
	width = 0;
	height = 0;
}

void Texture::handleEvent(SDL_Event& e)
{}
