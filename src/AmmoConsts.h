#pragma once
#include <map>
#include "Consts.h"

const SpriteParams BLAST_AMMO_TEXTURE_PARAMS = { "res/sprites/projectiles/blast.png", 30, 50, 1 };
const SpriteParams ROCKET_AMMO_TEXTURE_PARAMS = { "res/sprites/projectiles/rocket.png", 30, 50, 1 };

const SpriteParams BLAST_AMMO_LAUNCH_TEXTURE_PARAMS = { "res/sprites/projectiles/blast_launch.png", 30, 50, 1 };
const SpriteParams ROCKET_AMMO_LAUNCH_TEXTURE_PARAMS = { "res/sprites/projectiles/rocket_launch.png", 30, 50, 1 };

const SpriteParams BLAST_AMMO_EXPLOSION_TEXTURE_PARAMS = { "res/sprites/projectiles/blast_explosion.png", 30, 19, 5 };
const SpriteParams ROCKET_AMMO_EXPLOSION_TEXTURE_PARAMS = { "res/sprites/projectiles/blast_explosion.png", 30, 19, 5 };

const float BLAST_COOLDOWN = 200.0f;
const float ROCKET_COOLDOWN = 1000.0f;
const float LAZER_COOLDOWN = 0.0f;

const int BLAST_AMMO_SPEED = 8;
const int ROCKET_AMMO_SPEED = 4;
const int DIFFUSER_AMMO_SPEED = 3;
const int LAZER_AMMO_SPEED = 1000;

const int BLAST_DAMAGE = 50;
const int ROCKET_DAMAGE = 50;

const enum GunType
{
	BLAST,
	BLAST_DOUBLE,
	BLAST_DIFFUSER,

	ROCKET,
	ROCKET_DOUBLE,
	ROCKET_DIFFUSER,
};

const enum SUPPORTED_PJ_MANAGERS
{
	DOUBLE_PJ,
	DIFFUSER_PJ,
	SINGLE_PJ
};

struct GunParams
{
	float cooldownMs;
	std::string soundPath;
	SUPPORTED_PJ_MANAGERS pjManager;
};

#include "CollidersConsts.h"

struct AmmoParams
{
	int speed;
	SpriteParams texture;
	SpriteParams launchTexture;
	SpriteParams explosionTexture;
	Colliders colliders;
	CollidableType collidableType;
};

#include "Texture.h"

struct PJ_Textures {
	Texture* flying;
	Texture* launch;
	Texture* explosion;
};

struct PJ_Params {
	Vector2 position;
	GunType gun;
	int speed;
	Vector2 direction;
	int rotation;
	PJ_Textures textures;
};

#include "SoundConst.h"
#include "AmmoParams.h"

const std::map<GunType, GunParams> GUN_PARAMS =
{
	{ BLAST, BLAST_GUN_PARAMS },
	{ BLAST_DOUBLE, BLAST_DOUBLE_GUN_PARAMS },
	{ BLAST_DIFFUSER, BLAST_DIFFUSER_GUN_PARAMS },

	{ ROCKET, ROCKET_GUN_PARAMS },
	{ ROCKET_DOUBLE, ROCKET_DOUBLE_GUN_PARAMS },
	{ ROCKET_DIFFUSER, ROCKET_DIFFUSER_GUN_PARAMS },
};

const std::map<GunType, AmmoParams> AMMO_PARAMS
{
	{ BLAST, BLAST_PJ_PARAMS},
	{ BLAST_DOUBLE, BLAST_PJ_PARAMS},
	{ BLAST_DIFFUSER, BLAST_DIFFUSER_PJ_PARAMS },

	{ ROCKET, ROCKET_PJ_PARAMS},
	{ ROCKET_DOUBLE, ROCKET_PJ_PARAMS},
	{ ROCKET_DIFFUSER, ROCKET_DIFFUSER_PJ_PARAMS },
};

int getRadius(GunType type);