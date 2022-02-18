#pragma once

struct SpriteParams
{
	int imageW;
	int imageH;
	int length;
};

const enum GunTypes { ROCKET, LAZER };

struct ShipParams {
	SpriteParams sprite;
	GunTypes gunType;
	// ...other params
};

const SpriteParams DEFAULT_PLAYER_SHIP_SPRITE_PARAMS = { 102, 114, 10 };

const enum TextureTypes { TEXTURE_SPRITE, TEXTURE_FILE };

struct TextureParams
{
	TextureTypes type;
	std::string path;
	SpriteParams spriteParams;
};

