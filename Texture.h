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
	Texture(SDL_Renderer* p_renderer);
	~Texture();

	bool loadFromFile(std::string path, RGB* colorKeyRGB = NULL);
	bool loadFromSprite(std::string, SpriteParams params, RGB* colorKeyRGB = NULL);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

	int getWidth();
	int getHeight();
	std::vector<SDL_Rect>& getClips();

	void virtual onBeforeRender();
	void virtual onAfterRender();
	void virtual handleEvent(SDL_Event& e);
private: 
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	std::vector<SDL_Rect> spriteClips;
	int width;
	int height;
};