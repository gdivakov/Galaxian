#pragma once
#include <iostream>
#include <vector>

#include "Vector2.h"
#include "Consts.h"	
#include "SoundConst.h"
#include "Texture.h"

const SpriteParams SONIC_A_SHIP = { "res/sprites/ships/shipA.png", 102, 114, 10 };
const SpriteParams SONIC_B_SHIP = { "res/sprites/ships/shipB.png", 102, 123, 10 };
const SpriteParams SONIC_C_SHIP = { "res/sprites/ships/shipC.png", 75, 129, 10 };

const SpriteParams PIRATE_A_SHIP = { "res/sprites/ships/pirateA.png", 65, 144, 10 };
const SpriteParams BOSS_A_SHIP = { "res/sprites/ships/bossA.png", 300, 195, 9 };

const SpriteParams SONIC_A_SHIP_EXPLOSION = { "res/sprites/ships/explosion_sonicA.png", 165, 114, 9 };
const SpriteParams SONIC_B_SHIP_EXPLOSION = { "res/sprites/ships/explosion_sonicB.png", 176, 123, 9 };
const SpriteParams SONIC_C_SHIP_EXPLOSION = { "res/sprites/ships/explosion_sonicC.png", 165, 129, 9 };

const SpriteParams PIRATE_A_SHIP_EXPLOSION = { "res/sprites/ships/explosion_pirateA.png", 103, 144, 8 };
const SpriteParams BOSS_A_SHIP_EXPLOSION = { "res/sprites/ships/explosion_bossA.png", 300, 191, 10 };


const SpriteParams SONIC_A_SHIP_PREVIEW = { "res/sprites/ships/preview/sonicA.png", 150, 168, 10 };
const SpriteParams SONIC_B_SHIP_PREVIEW = { "res/sprites/ships/preview/sonicB.png", 150, 182, 10 };
const SpriteParams SONIC_C_SHIP_PREVIEW = { "res/sprites/ships/preview/sonicC.png", 150, 258, 10 };

const int SONIC_A_SPEED = 6;
const int PIRATE_A_SPEED = 5;
const int BOSS_A_SPEED = 5; // Todo: replace by certain categories

const int THIN_SHIP_HEALTH = 100;
const int AVERAGE_SHIP_HEALTH = 500;
const int STRONG_SHIP_HEALTH = 1000;

const int ARMOR_MULTIPLIER = 3;
const int THIN_SHIP_ARMOR = THIN_SHIP_HEALTH * ARMOR_MULTIPLIER;
const int AVERAGE_SHIP_ARMOR = AVERAGE_SHIP_HEALTH * ARMOR_MULTIPLIER;
const int STRONG_SHIP_ARMOR = STRONG_SHIP_HEALTH * ARMOR_MULTIPLIER;

const enum GunType { BLAST, ROCKET, ROCKET_DOUBLE, DIFFUSER, LAZER };
const enum ShipType { SONIC_A, SONIC_B, SONIC_C, PIRATE_A, BOSS_A };
const enum Space { WORLD, LOCAL };

struct RectColliderPoint
{
	Vector2 a; // Top Left
	Vector2 b; // Top Right
	Vector2 c; // Bottom Right
	Vector2 d; // Bottom Left
};

typedef std::vector<RectColliderPoint> Colliders;

struct ShipRect {
	Vector2 pos;
	Size size;
};

struct ShipParams {
	ShipType type;
	SpriteParams sprite;
	SpriteParams explosion;
	std::vector<GunType >guns;
	int maxSpeed;
	int armor;
	int health;
	const std::vector<RectColliderPoint>& colliders;
	std::string explosionSound;
};

struct Extrems {
	float min;
	float max;
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

const Colliders SONIC_A_COLLIDERS_DEFAULT =
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

const Colliders PIRATE_A_COLLIDERS_DEFAULT =
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

const int BOSS_A_IMG_HALF_W = BOSS_A_SHIP.imageW/2;
const int BOSS_A_IMG_HALF_H = BOSS_A_SHIP.imageH/2;

const Colliders BOSS_A_COLLIDERS_DEFAULT =
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

const float BLAST_COOLDOWN = 150.0f;
const float ROCKET_COOLDOWN = 1000.0f;
const float LAZER_COOLDOWN = 0.0f;

const int BLAST_AMMO_SPEED = 8;
const int ROCKET_AMMO_SPEED = 4;
const int DIFFUSER_AMMO_SPEED = 3;
const int LAZER_AMMO_SPEED = 1000;

const int BLAST_DAMAGE = 50;
const int ROCKET_DAMAGE = 50;

const SpriteParams BLAST_AMMO_TEXTURE_PARAMS = { "res/sprites/projectiles/blast.png", 30, 50, 1 };
const SpriteParams ROCKET_AMMO_TEXTURE_PARAMS = { "res/sprites/projectiles/rocket.png", 30, 50, 1 };
const SpriteParams LAZER_AMMO_TEXTURE_PARAMS = { "res/sprites/projectiles/lazer_ammo.png", 27, 111, 3 };

const SpriteParams BLAST_AMMO_LAUNCH_TEXTURE_PARAMS = { "res/sprites/projectiles/blast_launch.png", 30, 50, 1 };
const SpriteParams ROCKET_AMMO_LAUNCH_TEXTURE_PARAMS = { "res/sprites/projectiles/rocket_launch.png", 30, 50, 1 };

const SpriteParams BLAST_AMMO_EXPLOSION_TEXTURE_PARAMS = { "res/sprites/projectiles/blast_explosion.png", 30, 19, 5 };
const SpriteParams ROCKET_AMMO_EXPLOSION_TEXTURE_PARAMS = { "res/sprites/projectiles/blast_explosion.png", 30, 19, 5 };

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

const Colliders LAZER_AMMO_COLLIDER =
{
	{
		Vector2(-7.5, -25),
		Vector2(7.5, -25),
		Vector2(7.5, 25),
		Vector2(-7.5, 25)
	}
};

struct GunParams
{
	float cooldownMs;
	std::string soundPath;
};

const enum CollidableType 
{ 
	COLLIDABLE_SHIP, 
	COLLIDABLE_PROJECTILE_BLAST, 
	COLLIDABLE_PROJECTILE_ROCKET, 
	COLLIDABLE_BUFF,
	COLLIDABLE_METEORITE
};

struct AmmoParams
{
	int speed;
	SpriteParams texture;
	SpriteParams launchTexture;
	SpriteParams explosionTexture;
	Colliders colliders;
	CollidableType collidableType;
};

struct PJ_Textures { Texture* flying; Texture* launch; Texture* explosion; };
struct PJ_Params {
	Vector2 position;
	GunType gun;
	int speed;
	Vector2 direction;
	int rotation;
	PJ_Textures textures;
};

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
Colliders& addVectorToCollider(Colliders& colliders, Vector2& v);
Colliders& rotateColliders(Colliders& colliders, int angle);
RectColliderPoint getColliderProjectionOnAxis(RectColliderPoint& collider, Vector2 axis);
std::vector<float> getPointValuesOnAxis(RectColliderPoint& points, Vector2 axis);
float findMaxNumber(std::vector<float> nums);
float findMinNumber(std::vector<float> nums);
bool checkOverlapSAT(RectColliderPoint& coll1, RectColliderPoint& coll2);
void renderCollider(SDL_Renderer* renderer, RectColliderPoint& coll);

GunParams getGunParamsByType(GunType type);
AmmoParams getAmmoParamsByGunType(GunType type);
ShipParams getShipParams(const ShipType type);
std::vector<BezierCurve> getEnemyPathCurves(int enemyCounter);

int getRadius(GunType type);
bool isOutside(Vector2 pos);