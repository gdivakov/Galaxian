#pragma once
#include "SpecialsConsts.h"

const SpriteParams SPRITE_BUFF_SHIELD = { "res/sprites/ships/sonicA/buffs/shield.png", 114, 114, 11 };
const SpriteParams SPRITE_BUFF_ARMOR_UP = { "res/sprites/ships/sonicA/buffs/armorUp.png", 114, 114, 9 };
const SpriteParams SPRITE_BUFF_BREAK_HAND = { "res/sprites/ships/sonicA/buffs/breakHand.png", 114, 114, 8 };
const SpriteParams SPRITE_BUFF_HEALTH_UP = { "res/sprites/ships/sonicA/buffs/healthUp.png", 114, 114, 9 };
const SpriteParams SPRITE_BUFF_SAVE_HAND = { "res/sprites/ships/sonicA/buffs/saveHand.png", 114, 114, 9 };
const SpriteParams SPRITE_BUFF_SPEED_UP = { "res/sprites/ships/sonicA/buffs/speedUp.png", 114, 114, 9 };
const SpriteParams SPRITE_BUFF_SUPERPOWER = { "res/sprites/ships/sonicA/buffs/superpower.png", 114, 114, 9 };

const BuffParams ARMOR_UP_BUFF_PARAMS = 
{ 
	BUFF_ARMOR_UP, 
	0, 
	{ "res/icons/buffs/armorUp.jpg", 35, 35, 1 }, 
	{ "res/icons/buffs/circled/armorUp.png", 50, 50, 1 }, 
	0, 
	false 
};

const BuffParams BREAK_HAND_BUFF_PARAMS = 
{ 
	BUFF_BREAK_HAND, 
	5 * MS_IN_SEC, 
	{ "res/icons/buffs/breakHand.jpg", 35, 35, 1 },
	{ "res/icons/buffs/circled/breakHand.png", 50, 50, 1 },
	0, 
	true 
};

const BuffParams HEALTH_UP_BUFF_PARAMS = 
{ 
	BUFF_HEALTH_UP, 
	0, 
	{ "res/icons/buffs/healthUp.jpg", 35, 35, 1 }, 
	{ "res/icons/buffs/circled/healthUp.png", 50, 50, 1 }, 
	0, 
	false 
};

const BuffParams SAVE_HAND_BUFF_PARAMS = 
{ 
	BUFF_SAVE_HAND, 
	30 * MS_IN_SEC, 
	{ "res/icons/buffs/saveHand.jpg", 35, 35, 1 }, 
	{ "res/icons/buffs/circled/saveHand.png", 50, 50, 1 }, 
	0, 
	false 
};

const BuffParams SHIELD_BUFF_PARAMS =
{ 
	BUFF_SHIELD, 
	10 * MS_IN_SEC, 
	{ "res/icons/buffs/shield.jpg", 35, 35, 1 }, 
	{ "res/icons/buffs/circled/shield.png", 50, 50, 1 }, 
	0, 
	true 
};

const BuffParams SPEED_UP_BUFF_PARAMS = 
{ 
	BUFF_SPEED_UP, 
	5 * MS_IN_SEC, 
	{ "res/icons/buffs/speedUp.jpg", 35, 35, 1 }, 
	{ "res/icons/buffs/circled/speedUp.png", 50, 50, 1 }, 
	0, 
	true 
};

const BuffParams SUPERPOWER_BUFF_PARAMS = 
{ 
	BUFF_SUPERPOWER, 
	15 * MS_IN_SEC, 
	{ "res/icons/buffs/superpower.jpg", 35, 35, 1 }, 
	{ "res/icons/buffs/circled/superpower.png", 50, 50, 1 }, 
	0, 
	true 
};
