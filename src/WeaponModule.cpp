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

bool WeaponModule::fire()
{
	if (isOnCooldown || ship->getIsAccelerated())
	{
		return false;
	}

	system->getAudioPlayer()->playSound(fireSound);
	ammo->startProjectile();

	if (cooldownMs != 0) {
		isOnCooldown = true;
		cooldownTimer.start();
	}

	return true;
}

void WeaponModule::handleEvent(SDL_Event& e)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (!isEnemyShip) 
	{
		if (currentKeyStates[SDL_SCANCODE_L] || currentKeyStates[SDL_SCANCODE_SPACE])
		{
			fire();
			return;
		}
	}
}
void WeaponModule::onBeforeRender()
{
	if (isOnCooldown && cooldownTimer.getTicks() > cooldownMs)
	{
		isOnCooldown = false;
		cooldownTimer.stop();
	}
}

WeaponModule::~WeaponModule()
{
	delete ammo;

	ship = NULL;
	ammo = NULL;
	system = NULL;
}

