#include <iostream>
#include <vector>

#include "Timer.h"
#include "Projectile.h"
#include "Consts.h"

class Ship;
class Projectile;
class Texture;

class WeaponModule : public Texture
{
public:
	WeaponModule(
		GunType initGunType, 
		SDL_Renderer* renderer, 
		Ship* p_ship
	);
	void fire();
	void addGun();
	void removeGun();

	virtual void handleEvent(SDL_Event& e);
	virtual void onBeforeRender();
	virtual void onAfterRender();
	~WeaponModule();
private:
	bool isOnCooldown;
	float cooldownMs;
	short fireSoundId;
	GunType selectedGun;
	std::vector<GunType> availableGuns;
	Timer cooldownTimer;
	Ship* ship;
	Projectile ammo;
};

const float ROCKET_COOLDOWN = 100.0f;
const float LAZER_COOLDOWN = 0;
const TextureParams ROCKET_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/rocket.png" };
const TextureParams LAZER_TEXTURE_PARAMS = { TEXTURE_SPRITE, "res/lazer.png" };

struct GunParams
{
	float cooldownMs;
	TextureParams texture;
};
