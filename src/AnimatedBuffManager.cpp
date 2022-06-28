#include "AnimatedBuffManager.h"
#include "Loop.h"

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

	loadFromSprite(BUFF_SPRITE_PARAMS.at(type));
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
