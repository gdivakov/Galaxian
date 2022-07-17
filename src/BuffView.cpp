#include <iostream>

#include "BuffView.h"

const float BUFF_FLYING_SPEED = BG_SCROLLING_SPEED + 2.7;

BuffView::BuffView(LevelBase* p_level, Vector2 pos, BuffType spawnedBuff) 
: 
Texture(p_level->getSystem()->getRenderer()),
Collidable(p_level->getSystem()->getRenderer(), COLLIDABLE_BUFF, getBuffParamsByType(BUFF_RANDOM).sprite.imageH/2)
{
	position = pos;
	level = p_level;
	BuffParams params = getBuffParamsByType(BUFF_RANDOM);
	buffType = params.type;

	loadFromFile(params.circledSprite.path);
}

BuffView::~BuffView()
{
	level = NULL;
}

void BuffView::onBeforeRender()
{
	if (!level->isPaused) // Buff is falling down
	{
		position = Vector2(position.x, position.y) + Vector2(0, BG_SCROLLING_SPEED_ACCELERATED / 4); 
	}

	shiftColliders();

	render(position - Vector2(size.w/2, size.h/2));

	checkCollision();
};

void BuffView::onAfterRender()
{
	const int windowHeight = level->getSystem()->getWindowSize()->h;

	if (position.y >= windowHeight)
	{
		unlink();
		level->getSpawner()->removeObject(this);
	}
}

void BuffView::handleCollided()
{
	Ship* collidedShip;

	switch (collidedTo->type) {
		case COLLIDABLE_SHIP:
			collidedShip = (Ship*)collidedTo;
			collidedShip->getSpecials()->buff->addBuff(buffType);

			unlink();
			level->getSpawner()->removeObject(this);
			break;
		default: 
			unlink();
			level->getSpawner()->removeObject(this);
	};
}