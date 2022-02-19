#pragma once

struct SpriteParams
{
	int imageW;
	int imageH;
	int length;
};

const enum GunType { ROCKET, LAZER };

struct ShipParams {
	SpriteParams sprite;
	GunType gunType;
	SDL_Rect rect;
	int maxVelocity;
	// ...other params
};

const SpriteParams DEFAULT_PLAYER_SHIP_SPRITE_PARAMS = { 102, 114, 10 };
const int SHIP_A_VELOCITY = 6;

const enum TextureTypes { TEXTURE_SPRITE, TEXTURE_FILE };

struct TextureParams
{
	TextureTypes type;
	std::string path;
	SpriteParams spriteParams;
};

