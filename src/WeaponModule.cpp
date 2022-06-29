#include "Ship.h"
#include "ShipConsts.h"
#include "SinglePJManager.h"
#include "DiffuserPJManager.h"
#include "DoublePJManager.h"

WeaponModule::WeaponModule(
	std::vector<GunType> guns,
	const App* p_system,
	Ship* p_ship
)
{
	system = p_system;
	ship = p_ship;
	pos = Vector2();
	isShootStarted = false;
	
	installedGuns = guns;
	selectGun(installedGuns.front());
	cooldownTimer = new Timer();
}

GunType WeaponModule::selectNextGun()
{
	auto selectedGunIt = std::find(installedGuns.begin(), installedGuns.end(), type);

	if (selectedGunIt == installedGuns.end())
	{
		std::cout << "Selected gun is not installed!" << std::endl; // Todo: add debug var and throw an exception here
		return *selectedGunIt;
	}

	if (selectedGunIt == installedGuns.end() - 1)
	{
		selectGun(installedGuns.front());
		return type;
	}

	selectGun(*(selectedGunIt + 1));
	return type;
}

void WeaponModule::selectGun(GunType nextGun)
{
	GunParams gunParams = GUN_PARAMS.at(nextGun);

	type = nextGun;
	isOnCooldown = false;

	// Set selected gun position dependent on Ship type
	ShipParams sParams = SHIP_PARAMS.at(ship->getType());

	if (sParams.gunPosition.find(type) != sParams.gunPosition.end())
	{
		setGunPos(sParams.gunPosition.at(type));
	}
	else
	{
		setGunPos(Vector2());
	}

	// Create gun if needed
	if (ammo[gunParams.pjManager])
	{
		return;
	}

	switch (type)
	{
	case ROCKET: 
	case BLAST:
		ammo[SINGLE_PJ] = new SinglePJManager(type, system, ship);
		break;
	case ROCKET_DIFFUSER:
	case BLAST_DIFFUSER:
		ammo[DIFFUSER_PJ] = new DiffuserPJManager(type, system, ship);
		break;
	case ROCKET_DOUBLE:
	case BLAST_DOUBLE:
		ammo[DOUBLE_PJ] = new DoublePJManager(type, system, ship);
		break;
	}
}

void WeaponModule::handleRender()
{
	if (ship->level->isPaused)
	{
		isShooting = false;
	}

	GunParams gunParams = GUN_PARAMS.at(type);

	if (isOnCooldown && cooldownTimer->getTicks() > gunParams.cooldownMs)
	{
		isOnCooldown = false;
		cooldownTimer->stop();
	}
	
	// Handle shooting
	if (isShooting && 
		!isOnCooldown && 
		!ship->level->getIsAccelerated() &&
		!ship->level->getIsCompleted() &&
		!ship->level->isPaused)
	{
		system->getAudioPlayer()->playSound(gunParams.soundPath);

		ammo[gunParams.pjManager]->startProjectile();

		if (gunParams.cooldownMs != 0) {
			isOnCooldown = true;
			cooldownTimer->start();
		}
	}
}

WeaponModule::~WeaponModule()
{
	for (auto& pjM : ammo)
	{
		delete pjM.second;
		pjM.second = nullptr;
	}

	delete cooldownTimer;

	cooldownTimer = nullptr;
	ship = nullptr;
	system = nullptr;
}

