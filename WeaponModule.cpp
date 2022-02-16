#include "WeaponModule.h"

const float ROCKET_COOLDOWN = 1000.0f;
const float LAZER_COOLDOWN = 0;
const TextureParams ROCKET_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/rocket.png" };
const TextureParams LAZER_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/lazer.png" };

struct GunParams 
{
	float cooldownMs;
	TextureParams texture;
};

GunParams getGunParamsByType(GunTypes type);

WeaponModule::WeaponModule(
	GunTypes initGunType,
	SDL_Renderer* p_renderer,
	SDL_Point* p_shipPosition
) : Texture(p_renderer), ammo(initGunType, p_renderer)
{
	shipPosition = p_shipPosition;
	isOnCooldown = false;

	// Prepare gun
	GunParams gunParams = getGunParamsByType(initGunType);
	cooldownMs = gunParams.cooldownMs;

	availableGuns.push_back(initGunType);
	selectedGun = availableGuns[0];
}

void WeaponModule::fire()
{
	if (isOnCooldown)
	{
		return;
	}
	ammo.startProjectile(shipPosition);

	if (cooldownMs != 0) {
		isOnCooldown = true;
		cooldownTimer.start();
	}
}

void WeaponModule::addGun()
{
	//Gun rocket = { ROCKET, 1000, 100, { SPRITE, "res/rocket.png" }, Projectile(ROCKET) };
	//Gun lazer = { LAZER, 0, 100, { SPRITE, "res/lazer.png" }, Projectile(LAZER) };
}

void WeaponModule::removeGun()
{}

void WeaponModule::handleEvent(SDL_Event& e)
{
	ammo.handleEvent(e);

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_l:
			fire();
			break;
		}
	}
}
void WeaponModule::onBeforeRender()
{
	ammo.onBeforeRender();

	if (isOnCooldown && cooldownTimer.getTicks() > cooldownMs)
	{
		isOnCooldown = false;
		cooldownTimer.stop();
	}
}

void WeaponModule::onAfterRender()
{
	ammo.onAfterRender();
}

WeaponModule::~WeaponModule()
{

}

GunParams getGunParamsByType(GunTypes type)
{
	switch (type)
	{
	case ROCKET:
		return { ROCKET_COOLDOWN, ROCKET_TEXTURE_PARAMS };
		break;
	case LAZER:
		return { LAZER_COOLDOWN, LAZER_TEXTURE_PARAMS };
		break;
	default:
		return { ROCKET_COOLDOWN, ROCKET_TEXTURE_PARAMS };
	}
}