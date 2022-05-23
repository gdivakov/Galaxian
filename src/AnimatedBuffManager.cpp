#include "AnimatedBuffManager.h"
#include "Loop.h"

const SpriteParams SONIC_A_BUFF_SHIELD = { "res/sprites/ships/sonicA/buffs/shield.png", 114, 114, 11 };
const SpriteParams SONIC_A_BUFF_ARMOR_UP = { "res/sprites/ships/sonicA/buffs/armorUp.png", 114, 114, 9 };
const SpriteParams SONIC_A_BUFF_BREAK_HAND = { "res/sprites/ships/sonicA/buffs/breakHand.png", 114, 114, 8 };
const SpriteParams SONIC_A_BUFF_HEALTH_UP = { "res/sprites/ships/sonicA/buffs/healthUp.png", 114, 114, 9 };
const SpriteParams SONIC_A_BUFF_SAVE_HAND = { "res/sprites/ships/sonicA/buffs/saveHand.png", 114, 114, 9 };
const SpriteParams SONIC_A_BUFF_SPEED_UP = { "res/sprites/ships/sonicA/buffs/speedUp.png", 114, 114, 9 };
const SpriteParams SONIC_A_BUFF_SUPERPOWER = { "res/sprites/ships/sonicA/buffs/superpower.png", 114, 114, 9 };

SpriteParams getBuffSpriteParams(BuffType type)
{
	if (type == BUFF_SHIELD) return SONIC_A_BUFF_SHIELD;
	if (type == BUFF_ARMOR_UP) return SONIC_A_BUFF_ARMOR_UP;
	if (type == BUFF_BREAK_HAND) return SONIC_A_BUFF_BREAK_HAND;
	if (type == BUFF_SAVE_HAND) return SONIC_A_BUFF_SAVE_HAND;
	if (type == BUFF_SPEED_UP) return SONIC_A_BUFF_SPEED_UP;
	if (type == BUFF_SUPERPOWER) return SONIC_A_BUFF_SUPERPOWER;
	if (type == BUFF_HEALTH_UP) return SONIC_A_BUFF_HEALTH_UP;
}

AnimatedBuffManager::~AnimatedBuffManager()
{
	for (AnimatedBuffs::iterator i = animatedBuffs.begin(); i != animatedBuffs.end(); i++)
	{
		delete i->second;
	}

	animatedBuffs.clear();
	ship = NULL;
};

void AnimatedBuffManager::loadBuffAnimation(BuffType type)
{
	if (!animatedBuffs[type])
	{
		animatedBuffs[type] = new AnimatedBuff(ship->level, type, ship, this);
		return;
	}

	animatedBuffs[type]->resetDuration();
}

void AnimatedBuffManager::checkBuffs()
{
	Uint32 currentTime = ship->level->getSystem()->getTimer()->getTicks();

	for (AnimatedBuffs::iterator i = animatedBuffs.begin(); i != animatedBuffs.end();)
	{
		AnimatedBuff* buff = i->second;
		bool isApplied = currentTime - buff->startedAt < buff->duration;

		if (!isApplied) // Remove animated buff
		{
			Loop* gameLoop = ship->level->getSystem()->getGameLoop();

			delete buff;

			i = animatedBuffs.erase(i++);
		}
		else
		{
			++i;
		}
	}
}

AnimatedBuff::AnimatedBuff(LevelBase* p_level, BuffType p_buffType, Ship* p_ship, AnimatedBuffManager* p_manager)
: Texture(p_level->getSystem()->getRenderer())
{
	Uint32 currentTime = p_ship->level->getSystem()->getTimer()->getTicks();
	Loop* gameLoop = p_ship->level->getSystem()->getGameLoop();

	BuffParams params = getBuffParamsByType(p_buffType, currentTime);
	duration = params.duration;
	startedAt = params.startTime;
	isCycled = params.isAnimCycled;
	type = p_buffType;
	frame = 0;
	isActive = true;
	ship = p_ship;
	level = p_level;
	manager = p_manager;

	loadFromSprite(getBuffSpriteParams(type));
	gameLoop->addRenderListener(this);
}

AnimatedBuff::~AnimatedBuff()
{
	Loop* gameLoop = level->getSystem()->getGameLoop();

	gameLoop->removeRenderListener(this);

	ship = NULL;
}


void AnimatedBuff::onBeforeRender()
{
	if (!isActive)
	{
		return;
	}

	Uint32 currentTime = level->getSystem()->getTimer()->getTicks();

	std::vector<SDL_Rect>& shipClips = getClips();

	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

	Vector2 center(size.w / 2, size.h / 2);
	render(ship->getRect().pos - center, currentClip);
}

void AnimatedBuff::onAfterRender()
{
	if (!isActive)
	{
		return;
	}

	int clipLength = getClips().size();

	++frame;

	if (frame / clipLength >= clipLength)
	{
		if (isCycled)
		{
			resetAnimation();
		}
		else {
			stopAnimation();
		}
	}

	if (isCycled)
	{
		manager->checkBuffs();
	}
}

void AnimatedBuff::resetDuration()
{
	Uint32 currentTime = level->getSystem()->getTimer()->getTicks();
	Loop* gameLoop = level->getSystem()->getGameLoop();
	
	isActive = true;
	startedAt = currentTime;
	gameLoop->removeRenderListener(this); // Render next buff animimation on top
	gameLoop->addRenderListener(this);
}
