#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

#include "Object.h"
#include "Vector2.h"
#include "Consts.h"

struct RGB;
struct SpriteParams;

class Texture: public Object
{
public: 
	typedef std::vector<SDL_Rect> Clips;

	Texture(SDL_Renderer* p_renderer);
	Texture(SDL_Renderer* p_renderer, SpriteParams sprite);
	Texture(SDL_Renderer* p_renderer, std::string path);
	virtual ~Texture();

	bool loadFromFile(std::string path, RGB* colorKeyRGB = NULL);
	bool loadFromSprite(SpriteParams params, RGB* colorKeyRGB = NULL);
	bool loadFromRenderedText(TTF_Font* font, std::string textureText, SDL_Color textColor);
	void render(Vector2 pos, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void free();

	Size size;

	Clips& getClips();

	void virtual handleEvent(SDL_Event& e) {};
private: 
	SDL_Texture* texture;
	Clips spriteClips;
protected:
	SDL_Renderer* renderer;

};