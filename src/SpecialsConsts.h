#pragma once
#include "Consts.h"
#include <map>

const enum BuffType {
	BUFF_RANDOM,
	BUFF_ARMOR_UP,
	BUFF_BREAK_HAND,
	BUFF_HEALTH_UP,
	BUFF_SAVE_HAND,
	BUFF_SHIELD,
	BUFF_SPEED_UP,
	BUFF_SUPERPOWER
};

struct BuffParams
{
	BuffType type;
	int duration;
	SpriteParams sprite;
	SpriteParams circledSprite;
	Uint32 startTime;
	bool isAnimCycled;
};

const int MS_IN_SEC = 1000;

#include "BuffParams.h"

const std::map<BuffType, BuffParams> BUFF_PARAMS =
{
	{ BUFF_ARMOR_UP, ARMOR_UP_BUFF_PARAMS },
	{ BUFF_BREAK_HAND, BREAK_HAND_BUFF_PARAMS },
	{ BUFF_HEALTH_UP, HEALTH_UP_BUFF_PARAMS },
	{ BUFF_SAVE_HAND, SAVE_HAND_BUFF_PARAMS },
	{ BUFF_SHIELD, SHIELD_BUFF_PARAMS },
	{ BUFF_SPEED_UP, SPEED_UP_BUFF_PARAMS },
	{ BUFF_SUPERPOWER, SUPERPOWER_BUFF_PARAMS }
};

const std::map<BuffType, SpriteParams> BUFF_SPRITE_PARAMS =
{
	{ BUFF_SHIELD, SPRITE_BUFF_SHIELD },
	{ BUFF_ARMOR_UP, SPRITE_BUFF_ARMOR_UP },
	{ BUFF_BREAK_HAND, SPRITE_BUFF_BREAK_HAND },
	{ BUFF_SAVE_HAND, SPRITE_BUFF_SAVE_HAND },
	{ BUFF_SPEED_UP, SPRITE_BUFF_SPEED_UP },
	{ BUFF_SUPERPOWER, SPRITE_BUFF_SUPERPOWER },
	{ BUFF_HEALTH_UP, SPRITE_BUFF_HEALTH_UP }
};

BuffParams getBuffParamsByType(BuffType type, Uint32 time = 0);