#pragma once
#include <SDL.h>
#include <map>

#include "Texture.h"
#include "SpecialsConsts.h"
#include "ShipConsts.h"
#include "Ship.h"
#include "LevelBase.h"

class Ship;
class LevelBase;
class AnimatedBuff;

struct AnimBuffParams
{
	Uint32 startedAt;
	int duration;
	BuffType type;
};

class AnimatedBuffManager
{
public:
	typedef std::map<BuffType, AnimatedBuff*> AnimatedBuffs;
	AnimatedBuffManager(Ship* p_ship) : ship(p_ship) {};
	~AnimatedBuffManager();
	void loadBuffAnimation(BuffType type);
	void checkBuffs();
private:
	Ship* ship;
	AnimatedBuffs animatedBuffs;
};

class AnimatedBuff : public Texture
{
public:
	AnimatedBuff(LevelBase* p_level, BuffType p_buffType, Ship* p_ship, AnimatedBuffManager* p_manager);
	~AnimatedBuff();
	virtual void onBeforeRender();
	virtual void onAfterRender();
	void resetAnimation() { frame = 0; };
	void resetDuration();
	void stopAnimation() { isActive = false; frame = 0; };

	BuffType type;
	int frame;
	int duration;
	Uint32 startedAt;
	bool isCycled;
private:
	bool isActive;
	Ship* ship;
	LevelBase* level;
	AnimatedBuffManager* manager;
};