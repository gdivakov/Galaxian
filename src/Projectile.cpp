#include <iostream>

#include "Projectile.h"
#include "Vector2.h"

const int SPEED_DIVIDER = 50;

Projectile::Projectile(GunType p_type, SDL_Renderer* p_renderer, Ship* p_ship) : Texture(p_renderer)
{
	AmmoParams params = getAmmoParamsByGunType(gunType);

	size = { params.texture.imageW, params.texture.imageH };
	speed = params.speed;
	gunType = p_type;
	ship = p_ship;

	loadFromSprite(params.texture.path, params.texture);

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

	releasedPjs.push_back({ nextPos, ship->getDirection(LOCAL), ship->getRotation(), 0, false });
}

void Projectile::move(FlyingProjectile* pj)
{
	//pj->position.y -= speed;
	pj->position = pj-> position + pj->direction * speed/SPEED_DIVIDER;
}

void Projectile::handleEvent(SDL_Event& e)
{}

void Projectile::onBeforeRender()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		FlyingProjectile& pj = releasedPjs[i];

		if (pj.isStarted && !ship->level->isPaused)
		{
			move(&pj); 
		}

		// Limit clips if exploaded
		SDL_Rect* currentClip = 
			pj.isStarted ? 
			clips[pj.frame / clips.size()]:
			explosionClips[pj.frame / explosionClips.size()];

		Vector2 nextPos = releasedPjs[i].position - Vector2(size.w / 2, size.h / 2);
		render(nextPos, currentClip, releasedPjs[i].rotation);
	}
}

void Projectile::onAfterRender()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		FlyingProjectile& pj = releasedPjs[i];
		short clipLength = pj.isStarted ? clips.size() : explosionClips.size();
		
		if (++pj.frame / clipLength >= clipLength)
		{
			if (!pj.isStarted)
			{
				pj.isStarted = true;
			}
			pj.frame = 0;
		}

		// Remove missed projectiles
		if (pj.position.y < 0 || pj.position.x < 0)
		{
			releasedPjs.erase(releasedPjs.begin() + i);
		}
	}
}