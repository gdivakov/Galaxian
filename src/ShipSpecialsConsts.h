#pragma once
#include "Consts.h"

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

BuffParams getBuffParamsByType(BuffType type, Uint32 time = 0);

const BuffParams armorUp = { BUFF_ARMOR_UP, 0, { "res/icons/buffs/armorUp.jpg", 35, 35, 1}, { "res/icons/buffs/circled/armorUp.png", 50, 50, 1}, 0, false };
const BuffParams breakHand = { BUFF_BREAK_HAND, 5 * MS_IN_SEC, { "res/icons/buffs/breakHand.jpg", 35, 35, 1}, { "res/icons/buffs/circled/breakHand.png", 50, 50, 1}, 0, true };
const BuffParams healthUp = { BUFF_HEALTH_UP, 0, { "res/icons/buffs/healthUp.jpg", 35, 35, 1}, { "res/icons/buffs/circled/healthUp.png", 50, 50, 1}, 0, false };
const BuffParams saveHand = { BUFF_SAVE_HAND, 60 * MS_IN_SEC, { "res/icons/buffs/saveHand.jpg", 35, 35, 1}, { "res/icons/buffs/circled/saveHand.png", 50, 50, 1}, 0, false };
const BuffParams shield = { BUFF_SHIELD, 10 * MS_IN_SEC, { "res/icons/buffs/shield.jpg", 35, 35, 1}, { "res/icons/buffs/circled/shield.png", 50, 50, 1}, 0, true };
const BuffParams speedUp = { BUFF_SPEED_UP, 5 * MS_IN_SEC, { "res/icons/buffs/speedUp.jpg", 35, 35, 1}, { "res/icons/buffs/circled/speedUp.png", 50, 50, 1}, 0, true };
const BuffParams superpower = { BUFF_SUPERPOWER, 15 * MS_IN_SEC, { "res/icons/buffs/superpower.jpg", 35, 35, 1}, { "res/icons/buffs/circled/superpower.png", 50, 50, 1}, 0, true };

const std::vector<const BuffParams*> availableBuffParams = { &armorUp, &breakHand, &healthUp, &saveHand, &shield, &speedUp, &superpower };