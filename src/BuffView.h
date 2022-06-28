#pragma once
#include <SDL.h>

#include "Texture.h"
#include "LevelBase.h"
#include "Vector2.h"
#include "SpecialsConsts.h"
#include "Consts.h"
#include "Collidable.h"

class BuffView : public Texture, public Collidable
{
public:
	BuffView(LevelBase* p_level, Vector2 pos, BuffType spawnedBuff);
	~BuffView();

	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent(SDL_Event& e) {};
	virtual void handleCollided();
private:
	Vector2 position;
	LevelBase* level;
	BuffType buffType;
protected:
	virtual void shiftColliders() { wrapperCollider.pos = position; };
	virtual void destroyCollidable() {};
};

