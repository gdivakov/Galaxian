#pragma once
#include "Vector2.h"
#include <math.h>
#include <vector>
#include <SDL.h>

const int WINDOWED_WIDTH = 920;
const int WINDOWED_HEIGHT = 620;

const enum GunType { ROCKET, LAZER }; // Todo: rocket - rename to blaster
const enum ShipType { SONIC_A, PIRATE_A }; // SONIC - player ship name
const enum Space { WORLD, LOCAL };

const struct BezierCurve {
	Vector2 p0;
	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	Vector2 getPoint(float t)
	{
		float tt = t * t;
		float ttt = tt * t;
		float u = 1.0f - t;
		float uu = u * u;
		float uuu = uu * u;

		Vector2 point = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);
		point.x = round(point.x);
		point.y = round(point.y);

		return point;
	}
};

struct SpriteParams
{
	std::string path;
	int imageW;
	int imageH;
	int length;
};

const SpriteParams SONIC_A_SHIP = { "res/shipA.png", 102, 114, 10 };
const SpriteParams PIRATE_A_SHIP = { "res/pirateA.png", 65, 144, 10 };

const int SONIC_A_SPEED = 6;
const int PIRATE_A_SPEED = 5;
const float RAD_TO_DEG = 180.0f / M_PI;
const float DEG_TO_RAD = M_PI / 180;

const SDL_Color textColor = { 0, 0, 0 };
const SDL_Color selectedOptionColor = { 1, 98, 177 };
const SDL_Color selectedDisabledOptionColor = { 153, 153, 153 };

struct RectColliderPoint
{
	Vector2 a; // Top Left
	Vector2 b; // Top Right
	Vector2 c; // Bottom Right
	Vector2 d; // Bottom Left
};

typedef std::vector<RectColliderPoint> Colliders;

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

struct ShipRect {
	Vector2 pos;
	Size size;
};

struct ShipParams {
	SpriteParams sprite;
	GunType gunType;
	int maxSpeed;
	std::vector<RectColliderPoint>& colliders;
};

static void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

struct Extrems {
	int min;
	int max;
};