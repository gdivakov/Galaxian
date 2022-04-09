#include <iostream>

#include "Projectile.h"
#include "Vector2.h"

const int SPEED_DIVIDER = 50;

Projectile::Projectile(GunType p_type, SDL_Renderer* p_renderer, Ship* p_ship) 
	: 
	Texture(p_renderer)
{
	AmmoParams params = getAmmoParamsByGunType(gunType);

	size = { params.texture.imageW, params.texture.imageH };
	speed = params.speed;
	gunType = p_type;
	ship = p_ship;

	loadFromSprite(params.texture);

	// Set up explosion and common clips
	Clips& pjClips = getClips();

	for (short i = 0; i < pjClips.size(); i++)
	{
		if (i < EXPLOSION_PROJECTILE_CLIP_LENGTH) // Todo: length should relate on type
		{
			explosionClips.push_back(&pjClips[i]);
		}
		else
		{
			clips.push_back(&pjClips[i]);
		}
	}
}

void Projectile::startProjectile()
{
	// Todo: relate x and y on gun position & rotation
	ShipRect shipRect = ship->getRect();
	Vector2 nextPos = ship->getDirection(LOCAL, false);

	nextPos = nextPos - Vector2(0, size.h / 2);
	nextPos = Vector2::getRotatedVector(nextPos, ship->getRotation()) + shipRect.pos;

	FlyingProjectile* nextProjectile = new FlyingProjectile(
		renderer, 
		nextPos, 
		ship->getDirection(LOCAL), 
		ship->getRotation(),
		gunType
	);

	std::vector<Collidable*> enemyCollidables = ship->getEnemyCollidables();

	for (int i = 0; i < enemyCollidables.size(); i++)
	{
		nextProjectile->registerEnemyCollidable(enemyCollidables[i]); // Todo: refactor (add plural method to Collidable class)
	}

	releasedPjs.push_back(nextProjectile);
}

void Projectile::move(FlyingProjectile* pj)
{
	Vector2 pjPosition = pj->getPosition();
	Vector2 pjDirection = pj->getDirection();

	pj->setPosition(pjPosition + pjDirection * speed / SPEED_DIVIDER);
	pj->shiftColliders();

	if (pj->checkCollision())
	{
		pj->handleCollided();
	}
}

void Projectile::onBeforeRender()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		FlyingProjectile* pj = releasedPjs[i];

		if (pj->getIsStarted() && !ship->level->isPaused)
		{
			move(pj); 
		}

		// Limit clips if exploaded
		SDL_Rect* currentClip = 
			pj->getIsStarted() ?
			clips[pj->getFrame() / clips.size()]:
			explosionClips[pj->getFrame() / explosionClips.size()];

		Vector2 nextPos = releasedPjs[i]->getPosition() - Vector2(size.w / 2, size.h / 2);

		releasedPjs[i]->showColliders();
		render(nextPos, currentClip, releasedPjs[i]->getRotation());
	}
}

void Projectile::onAfterRender()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		FlyingProjectile* pj = releasedPjs[i];
		short clipLength = pj->getIsStarted() ? clips.size() : explosionClips.size();
		short frame = pj->getFrame();

		if (pj->setFrame(frame + 1) / clipLength >= clipLength)
		{
			if (!pj->getIsStarted())
			{
				pj->setIsStarted(true);
			}
			pj->setFrame(0);
		}

		// Remove missed projectiles
		Vector2 pjPosition = pj->getPosition();

		if (pjPosition.y < 0 || pjPosition.x < 0)
		{
			delete releasedPjs[i];
			releasedPjs.erase(releasedPjs.begin() + i);
		}
	}
}