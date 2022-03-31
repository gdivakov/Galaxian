#pragma once
#include "Vector2.h";
#include <math.h>
#include <vector>
#include <SDL.h>

const int WINDOWED_WIDTH = 920;
const int WINDOWED_HEIGHT = 620;

struct SpriteParams
{
	int imageW;
	int imageH;
	int length;
};

const enum GunType { ROCKET, LAZER }; // Todo: rocket - rename to blaster
const enum ShipType { SONIC_A, PIRATE_A }; // SONIC - player ship name

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

struct ShipParams {
	SpriteParams sprite;
	GunType gunType;
	int maxSpeed;
};

//struct EnemyShipParams {
//	SpriteParams sprite;
//	GunType gunType;
//	int maxSpeed;
//	std::vector<BezierCurve> pathCurves;
//};

const SpriteParams SONIC_A_SHIP = { 102, 114, 10 };
const SpriteParams PIRATE_A_SHIP = { 65, 144, 10 };

const int SONIC_A_SPEED = 6;
const int PIRATE_A_SPEED = 5;

const enum TextureTypes { TEXTURE_SPRITE, TEXTURE_FILE };

struct TextureParams
{
	TextureTypes type;
	std::string path;
	SpriteParams spriteParams;
};

const float RAD_TO_DEG = 180.0f / M_PI;

const SDL_Color textColor = { 0, 0, 0 };
const SDL_Color selectedOptionColor = { 1, 98, 177 };
const SDL_Color selectedDisabledOptionColor = { 153, 153, 153 };

struct Circle
{
	int x, y;
	int r;
};

struct Size
{
	int w;
	int h;
};