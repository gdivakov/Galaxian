#pragma once
#include "Vector2.h";
#include <math.h>
#include <vector>

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
	ShipType type;
	SpriteParams sprite;
	GunType gunType;
	SDL_Rect rect;
	int maxVelocity;
	std::vector<BezierCurve> pathCurves;
	// ...other params
};

const SpriteParams SONIC_A_SHIP = { 102, 114, 10 };
const SpriteParams PIRATE_A_SHIP = { 65, 144, 10 };

const int SONIC_A_VELOCITY = 6;
const int PIRATE_A_VELOCITY = 5;

const enum TextureTypes { TEXTURE_SPRITE, TEXTURE_FILE };

struct TextureParams
{
	TextureTypes type;
	std::string path;
	SpriteParams spriteParams;
};

const float RAD_TO_DEG = 180.0f / M_PI;