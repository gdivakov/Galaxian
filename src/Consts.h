#pragma once

struct SpriteParams
{
	int imageW;
	int imageH;
	int length;
};

const enum GunType { ROCKET, LAZER }; // Todo: rocket - rename to blaster
const enum ShipType { SONIC_A, PIRATE_A }; // SONIC - player ship name

struct ShipParams {
	ShipType type;
	SpriteParams sprite;
	GunType gunType;
	SDL_Rect rect;
	int maxVelocity;
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

