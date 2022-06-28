#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "Consts.h"	
#include "Vector2.h"

const int SHIP_SPEED_FAST = 6;
const int SHIP_SPEED_AVERAGE = 5;

const int THIN_SHIP_HEALTH = 100;
const int AVERAGE_SHIP_HEALTH = 500;
const int STRONG_SHIP_HEALTH = 1000;

const int ARMOR_MULTIPLIER = 3;
const int THIN_SHIP_ARMOR = THIN_SHIP_HEALTH * ARMOR_MULTIPLIER;
const int AVERAGE_SHIP_ARMOR = AVERAGE_SHIP_HEALTH * ARMOR_MULTIPLIER;
const int STRONG_SHIP_ARMOR = STRONG_SHIP_HEALTH * ARMOR_MULTIPLIER;

#include "PlayerConsts.h"
#include "EnemyConsts.h"
#include "AmmoConsts.h"

const enum ShipType 
{ 
	SONIC_A, 
	SONIC_B, 
	SONIC_C, 

	PIRATE_A, 
	PIRATE_B, 
	PIRATE_C,
	PIRATE_D,
	PIRATE_E,
	PIRATE_F,
	
	BOSS_A 
};

struct ShipRect { Vector2 pos; Size size; };

#include "CollidersConsts.h"

struct ShipParams {
	ShipType type;
	SpriteParams sprite;
	SpriteParams explosion;
	SpriteParams accelerate;
	std::vector<GunType >guns;
	int maxSpeed;
	int armor;
	int health;
	const std::vector<RectColliderPoint>& colliders;
	std::string explosionSound;
};

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

#include "ShipParams.h"

const std::map<ShipType, ShipParams> SHIP_PARAMS = 
{
	{ SONIC_A, SONIC_A_PARAMS },
	{ SONIC_B, SONIC_B_PARAMS },
	{ SONIC_C, SONIC_C_PARAMS },

	{ PIRATE_A, PIRATE_A_PARAMS },
	{ PIRATE_B, PIRATE_B_PARAMS },
	{ PIRATE_C, PIRATE_C_PARAMS },
	{ PIRATE_D, PIRATE_D_PARAMS },
	{ PIRATE_E, PIRATE_E_PARAMS },
	{ PIRATE_F, PIRATE_F_PARAMS },

	{ BOSS_A, BOSS_A_PARAMS },
};

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
std::vector<BezierCurve> getEnemyPathCurves(int enemyCounter);