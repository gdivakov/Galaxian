#include "Ship.h"
#include "ShipConsts.h"
#include "SinglePJManager.h"
#include "DiffuserPJManager.h"
#include "DoublePJManager.h"

WeaponModule::WeaponModule(
	std::vector<GunType> guns,
	const App* p_system,
	Ship* p_ship,
	bool p_isEnemyShip
) : Texture(p_system->getRenderer()), system(p_system)
{
	ship = p_ship;
	isEnemyShip = p_isEnemyShip;
	pos = Vector2();

	selectGun(guns[0]);
}

void WeaponModule::selectGun(GunType nextGun)
{
	if (ammo)
	{
		delete ammo;
	}

	GunParams params = getGunParamsByType(nextGun);
	selectedGun = nextGun;
	cooldownMs = params.cooldownMs;
	fireSound = params.soundPath;
	isOnCooldown = false;

	// Todo: refactor here (Ammo constructor class should be part of constant)
	switch (selectedGun)
	{
	case ROCKET: 
	case BLAST:
		ammo = new SinglePJManager(selectedGun, system, ship);
		break;
	case DIFFUSER:
		ammo = new DiffuserPJManager(selectedGun, system, ship);
		break;
	case ROCKET_DOUBLE:
		ammo = new DoublePJManager(selectedGun, system, ship);
		break;
	}
}

void WeaponModule::handleEvent(SDL_Event& e)
{
	if (isEnemyShip)  // Todo: remove hardcode
	{
		return;
	}

	if (!ship->isActive)
	{
		isShooting = false;
	}

	if (e.type == SDL_KEYDOWN && !ship->level->getIsCompleted())
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
		case SDLK_l:
			isShooting = true;
			return;
		}
	}

	if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
		case SDLK_l:
			isShooting = false;
			return;
		}
	}
}

void WeaponModule::onBeforeRender()
{
	if (ship->level->isPaused)
	{
		isShooting = false;
	}

	if (isOnCooldown && cooldownTimer.getTicks() > cooldownMs)
	{
		isOnCooldown = false;
		cooldownTimer.stop();
	}

	// Shooting
	if (isShooting && 
		!isOnCooldown && 
		!ship->level->getIsAccelerated() &&
		!ship->level->getIsCompleted() &&
		!ship->level->isPaused
		)
	{
		system->getAudioPlayer()->playSound(fireSound);
		ammo->startProjectile();

		if (cooldownMs != 0) {
			isOnCooldown = true;
			cooldownTimer.start();
		}
	}
}

WeaponModule::~WeaponModule()
{
	delete ammo;

	ship = NULL;
	ammo = NULL;
	system = NULL;
}

