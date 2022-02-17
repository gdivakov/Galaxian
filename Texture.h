#pragma once 

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>

#include "Object.h"

struct RGB;
struct SpriteParams;

class Texture: public Object
{
public: 
	typedef std::vector<SDL_Rect> Clips;
	Texture(SDL_Renderer* p_renderer);
	virtual ~Texture();

	bool loadFromFile(std::string path, RGB* colorKeyRGB = NULL);
	bool loadFromSprite(std::string, SpriteParams params, RGB* colorKeyRGB = NULL);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

	int getWidth();
	int getHeight();
	Clips& getClips();

	void virtual handleEvent(SDL_Event& e);
private: 
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	Clips spriteClips;
	int width;
	int height;
};