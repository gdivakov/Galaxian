#pragma once

const int SCREEN_WIDTH = 920; // Todo: Remove usage of this vars as we pass it localy
const int SCREEN_HEIGHT = 620;// or remove localy

struct SpriteParams
{
	int imageW;
	int imageH;
	int length;
};

const SpriteParams DEFAULT_PLAYER_SHIP_SPRITE_PARAMS = { 109, 102, 3 };

const enum TextureTypes { TEXTURE_SPRITE, TEXTURE_FILE };

struct TextureParams
{
	TextureTypes type;
	std::string path;
	SpriteParams spriteParams;
};

const enum GunTypes { ROCKET, LAZER };