#include <iostream>

#include "Projectile.h"
#include "Consts.h"

struct AmmoParams
{
	int speed;
	TextureParams texture;
};

AmmoParams getAmmoParamsByGunType(GunTypes type);

const int ROCKET_AMMO_SPEED = 20;
const int LAZER_AMMO_SPEED = 1000;

TextureParams ROCKET_AMMO_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/rocket2.png", { 30, 76, 3 } };
TextureParams LAZER_AMMO_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/lazer_ammo.png" , { 27, 111, 3 } };

Projectile::Projectile(GunTypes p_type, SDL_Renderer* p_renderer) : Texture(p_renderer)
{
	AmmoParams params = getAmmoParamsByGunType(gunType);

	width = params.texture.spriteParams.imageW; // Todo: Only from sprites for now (add texture support)
	height = params.texture.spriteParams.imageH;

	vel = params.speed; // Todo: replace by velocity
	gunType = p_type;

	
	//if (params.texture.type == TEXTURE_SPRITE)
	//{
		loadFromSprite(params.texture.path, params.texture.spriteParams);

	//}
	//else
	//{
	//	loadFromFile(params.texture.path);
	//}
}

void Projectile::startProjectile(SDL_Point* shipPosition)
{
	// Todo: make widht/height const; replace 98 by shipWidth
	FlyingProjectile newProjectile = {
		{ shipPosition->x + (109 - width) / 2, shipPosition->y - height },
		0
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
	std::vector<SDL_Rect>& shipClips = getClips(); // add to flying object as rendered clips

	for (int i = 0; i < releasedPjs.size(); i++)
	{
		move(&releasedPjs[i]);
		SDL_Rect* currentClip = &shipClips[releasedPjs[i].frame / shipClips.size()];
		render(releasedPjs[i].position.x, releasedPjs[i].position.y, currentClip);
	}
}

void Projectile::onAfterRender()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		++releasedPjs[i].frame;

		if (releasedPjs[i].frame / 4 >= getClips().size()) // Todo: update
		{
			releasedPjs[i].frame = 0;
		}
	}
}

AmmoParams getAmmoParamsByGunType(GunTypes type)
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