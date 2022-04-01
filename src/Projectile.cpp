#include <iostream>

#include "Projectile.h"
#include "Vector2.h"

struct AmmoParams
{
	int speed;
	SpriteParams texture;
};

AmmoParams getAmmoParamsByGunType(GunType type);

const int EXPLOSION_PROJECTILE_CLIP_LENGTH = 1;
const int ROCKET_AMMO_SPEED = 8;
const int LAZER_AMMO_SPEED = 1000;

SpriteParams ROCKET_AMMO_TEXTURE_PARAMS = { "res/rocket3.png", 30, 50, 2 };
SpriteParams LAZER_AMMO_TEXTURE_PARAMS = { "res/lazer_ammo.png", 27, 111, 3 };

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

	ShipRect shipRect = ship->getRect();
	// Todo: relate x and y on gun position
	FlyingProjectile newProjectile = {
		{ shipRect.pos.x - size.w / 2, shipRect.pos.y - shipRect.size.h/2 - size.h },
		0,
		false
	};

	releasedPjs.push_back(newProjectile);
}

void Projectile::move(FlyingProjectile* pj)
{
	pj->position.y -= speed;
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

		render(Vector2(releasedPjs[i].position.x, releasedPjs[i].position.y), currentClip);
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

AmmoParams getAmmoParamsByGunType(GunType type)
{
	switch (type)
	{
	case ROCKET:
		return { ROCKET_AMMO_SPEED, ROCKET_AMMO_TEXTURE_PARAMS };
		break;
	case LAZER:
		return { LAZER_AMMO_SPEED, LAZER_AMMO_TEXTURE_PARAMS };
		break;
	default:
		return { ROCKET_AMMO_SPEED, ROCKET_AMMO_TEXTURE_PARAMS };
	}
}