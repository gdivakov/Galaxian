#pragma once
#include "Vector2.h"
#include "EnemyConsts.h"
#include "Consts.h"

const short SAT_AXES_TO_CHECK = 4;

struct RectColliderPoint
{
	Vector2 a; // Top Left
	Vector2 b; // Top Right
	Vector2 c; // Bottom Right
	Vector2 d; // Bottom Left
};

typedef std::vector<RectColliderPoint> Colliders;

const enum CollidableType
{
	COLLIDABLE_SHIP,
	COLLIDABLE_PROJECTILE_BLAST,
	COLLIDABLE_PROJECTILE_ROCKET,
	COLLIDABLE_BUFF,
	COLLIDABLE_METEORITE
};

const Colliders BLAST_AMMO_COLLIDER =
{
	{
		Vector2(-7.5, -25),
		Vector2(7.5, -25),
		Vector2(7.5, 25),
		Vector2(-7.5, 25)
	}
};

const Colliders ROCKET_AMMO_COLLIDER =
{
	{
		Vector2(-7.5, -16),
		Vector2(7.5, -16),
		Vector2(7.5, 16),
		Vector2(-7.5, 16)
	}
};

const Colliders SONIC_A_COLLIDERS =
{
	{
		Vector2(-15, -15 - 40),
		Vector2(15, -15 - 40),
		Vector2(15, 15 - 40),
		Vector2(-15, 15 - 40),
	},
	{
		Vector2(-50, -25),
		Vector2(50, -25),
		Vector2(50, 25),
		Vector2(-50, 25),
	}
};

const Colliders SONIC_C_COLLIDERS =
{
	SONIC_A_COLLIDERS[0],
	{
		Vector2(-25, -25),
		Vector2(25, -25),
		Vector2(25, 25),
		Vector2(-25, 25),
	}
};

const Colliders PIRATE_A_COLLIDERS =
{
	{
		Vector2(-9, -21 - 50),
		Vector2(9, -21 - 50),
		Vector2(9, 21 - 50),
		Vector2(-9, 21 - 50),
	},
	{
		Vector2(-32, -28),
		Vector2(32, -28),
		Vector2(32, 28),
		Vector2(-32, 28),
	}
};

const Colliders PIRATE_B_COLLIDERS =
{
	{
		Vector2(-9, -21 - 50),
		Vector2(9, -21 - 50),
		Vector2(9, 21 - 50),
		Vector2(-9, 21 - 50),
	},
	{
		Vector2(-32, -28),
		Vector2(32, -28),
		Vector2(32, 28),
		Vector2(-32, 28),
	}
};

const int BOSS_A_IMG_HALF_W = BOSS_A_SHIP.imageW / 2;
const int BOSS_A_IMG_HALF_H = BOSS_A_SHIP.imageH / 2;

const Colliders BOSS_A_COLLIDERS =
{
	{
		Vector2(-25, -BOSS_A_IMG_HALF_H + 15),
		Vector2(25, -BOSS_A_IMG_HALF_H + 15),
		Vector2(25, -BOSS_A_IMG_HALF_H + 40),
		Vector2(-25, -BOSS_A_IMG_HALF_H + 40),
	},
	{
		Vector2(-BOSS_A_IMG_HALF_W + 42, -BOSS_A_IMG_HALF_H + 40),
		Vector2(BOSS_A_IMG_HALF_W - 42, -BOSS_A_IMG_HALF_H + 40),
		Vector2(BOSS_A_IMG_HALF_W - 42, -BOSS_A_IMG_HALF_H + 77),
		Vector2(-BOSS_A_IMG_HALF_W + 42, -BOSS_A_IMG_HALF_H + 77),
	},
	{
		Vector2(-BOSS_A_IMG_HALF_W, -BOSS_A_IMG_HALF_H + 77),
		Vector2(BOSS_A_IMG_HALF_W, -BOSS_A_IMG_HALF_H + 77),
		Vector2(BOSS_A_IMG_HALF_W, BOSS_A_IMG_HALF_H - 21),
		Vector2(-BOSS_A_IMG_HALF_W, BOSS_A_IMG_HALF_H - 21),
	}
};

Colliders& addVectorToCollider(Colliders& colliders, Vector2& v);
Colliders& rotateColliders(Colliders& colliders, int angle);
RectColliderPoint getColliderProjectionOnAxis(RectColliderPoint& collider, Vector2 axis);
std::vector<float> getPointValuesOnAxis(RectColliderPoint& points, Vector2 axis);
bool checkOverlapSAT(RectColliderPoint& coll1, RectColliderPoint& coll2);
void renderCollider(SDL_Renderer* renderer, RectColliderPoint& coll);
float findMaxNumber(std::vector<float> nums); // Todo: replace by stl
float findMinNumber(std::vector<float> nums); // Todo: replace by stl
Extrems getExtrems(std::vector<float> values); // Todo: replace by stl