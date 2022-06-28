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
	
	installedGuns = guns;
	selectGun(installedGuns.front());
}

GunType WeaponModule::selectNextGun()
{
	auto selectedGunIt = std::find(installedGuns.begin(), installedGuns.end(), selectedGun);

	if (selectedGunIt == installedGuns.end())
	{
		std::cout << "Selected gun is not installed!" << std::endl;
		return *selectedGunIt;
	}

	if (selectedGunIt == installedGuns.end() - 1)
	{
		selectGun(installedGuns.front());
		return selectedGun;
	}

	selectGun(*(selectedGunIt + 1));
	return selectedGun;
}

void WeaponModule::selectGun(GunType nextGun)
{
	if (ammo)
	{
		delete ammo;
	}

	GunParams params = GUN_PARAMS.at(nextGun);
	selectedGun = nextGun;
	cooldownMs = params.cooldownMs;
	fireSound = params.soundPath;
	isOnCooldown = false;

	// Todo: refactor here (Ammo constructor class should be part of constant) 
	// Todo: maybe move to separate class
	switch (selectedGun)
	{
	case ROCKET: 
	case BLAST:
		ammo = new SinglePJManager(selectedGun, system, ship);
		break;
	case ROCKET_DIFFUSER:
	case BLAST_DIFFUSER:
		ammo = new DiffuserPJManager(selectedGun, system, ship);
		break;
	case ROCKET_DOUBLE:
	case BLAST_DOUBLE:
		ammo = new DoublePJManager(selectedGun, system, ship);
		break;
	}
}

void WeaponModule::handleRender()
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

	ship = nullptr;
	ammo = nullptr;
	system = nullptr;
}

