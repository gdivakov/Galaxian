#pragma once
#include <math.h>
#include <vector>
#include <SDL.h>

#include "Vector2.h"
#include "Consts.h"

const int WINDOWED_WIDTH = 920;
const int WINDOWED_HEIGHT = 620;

const int BG_SCROLLING_SPEED = 2;
const int ACCELERATION_SPEED_MP = 10;
const int BG_SCROLLING_SPEED_ACCELERATED = BG_SCROLLING_SPEED * ACCELERATION_SPEED_MP;

const float RAD_TO_DEG = 180.0f / M_PI;
const float DEG_TO_RAD = M_PI / 180;

const SDL_Color textColor = { 0, 0, 0 };
const SDL_Color whiteTextColor = { 255, 255, 255 };
const SDL_Color selectedOptionColor = { 1, 98, 177 };
const SDL_Color selectedDisabledOptionColor = { 153, 153, 153 };

struct SpriteParams
{
	std::string path;
	int imageW;
	int imageH;
	int length;
};

const std::string LEVEL1_BG_PATH = "res/sprites/backgrounds/space.png";
const std::string FONT_PATH = "res/Staatliches-Regular.ttf";

const int DEFAULT_FONT_SIZE = 35;
const int SMALL_FONT_SIZE = 20;
const int MEDIUM_FONT_SIZE = 30;
const int LARGE_FONT_SIZE = 45;

struct Circle
{
	Vector2 pos;
	int r;
};

struct Size
{
	int w;
	int h;
};

struct RGB {
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

struct Extrems {
	float min;
	float max;
};

const enum Space { WORLD, LOCAL };

inline int getRandom(int max)
{
	return rand() % max;
}