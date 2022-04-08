#pragma once
#include <math.h>
#include <vector>
#include <SDL.h>

#include "Vector2.h"
#include "Consts.h"

const int WINDOWED_WIDTH = 920;
const int WINDOWED_HEIGHT = 620;

const float RAD_TO_DEG = 180.0f / M_PI;
const float DEG_TO_RAD = M_PI / 180;

const SDL_Color textColor = { 0, 0, 0 };
const SDL_Color selectedOptionColor = { 1, 98, 177 };
const SDL_Color selectedDisabledOptionColor = { 153, 153, 153 };

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