#include <iostream>

#include "Projectile.h"

struct AmmoParams
{
	int speed;
	TextureParams texture;
};

AmmoParams getAmmoParamsByGunType(GunType type);

const int EXPLOSION_PROJECTILE_CLIP_LENGTH = 1;

const int ROCKET_AMMO_SPEED = 8;
const int LAZER_AMMO_SPEED = 1000;

TextureParams ROCKET_AMMO_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/rocket3.png", { 30, 50, 2 } };
TextureParams LAZER_AMMO_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/lazer_ammo.png" , { 27, 111, 3 } };

Projectile::Projectile(GunType p_type, SDL_Renderer* p_renderer) : Texture(p_renderer)
{
	AmmoParams params = getAmmoParamsByGunType(gunType);

	width = params.texture.spriteParams.imageW; // Todo: Only from sprites for now (add texture support)
	height = params.texture.spriteParams.imageH;
	vel = params.speed; // Todo: replace by velocity
	gunType = p_type;

	loadFromSprite(params.texture.path, params.texture.spriteParams);

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

	//if (params.texture.type == TEXTURE_SPRITE)
	//{
		//loadFromSprite(params.texture.path, params.texture.spriteParams);

	//}
	//else
	//{
	//	loadFromFile(params.texture.path);
	//}
}

void Projectile::startProjectile(const SDL_Rect* shipRect)
{
	// Todo: relate x and y on gun position
	FlyingProjectile newProjectile = {
		{ shipRect->x + (shipRect->w - width) / 2, shipRect->y - height },
		0,
		false
	};

	releasedPjs.push_back(newProjectile);
}

void Projectile::move(FlyingProjectile* pj)
{
	pj->position.y -= vel;
}

void Projectile::handleEvent(SDL_Event& e)
{}

void Projectile::onBeforeRender()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		FlyingProjectile& pj = releasedPjs[i];

		if (pj.isStarted)
		{
			move(&pj);
		}

		// Limit clips if exploaded
		SDL_Rect* currentClip = 
			pj.isStarted ? 
			clips[pj.frame / clips.size()]:
			explosionClips[pj.frame / explosionClips.size()];

		render(releasedPjs[i].position.x, releasedPjs[i].position.y, currentClip);
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