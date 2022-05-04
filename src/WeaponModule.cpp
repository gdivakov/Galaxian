#include "Ship.h"
#include "ShipConsts.h"

WeaponModule::WeaponModule(
	GunType initGunType,
	const App* p_system,
	Ship* p_ship,
	bool p_isEnemyShip
) : Texture(p_system->getRenderer()), system(p_system)
{
	ammo = new ProjectileManager(initGunType, system, p_ship);
	ship = p_ship;
	isOnCooldown = false;

	// Prepare gun
	GunParams params = getGunParamsByType(initGunType);
	cooldownMs = params.cooldownMs;
	fireSound = params.soundPath;

	//availableGuns.push_back(initGunType);
	selectedGun = initGunType;

	isEnemyShip = p_isEnemyShip;
}

void WeaponModule::fire()
{
	if (isOnCooldown)
	{
		return;
	}

	system->getAudioPlayer()->playSound(fireSound);
	ammo->startProjectile();


	if (cooldownMs != 0) {
		isOnCooldown = true;
		cooldownTimer.start();
	}
}

void WeaponModule::addGun()
{
	//Gun rocket = { BLAST, 1000, 100, { SPRITE, "res/rocket.png" }, Projectile(BLAST) };
	//Gun lazer = { LAZER, 0, 100, { SPRITE, "res/lazer.png" }, Projectile(LAZER) };
}

void WeaponModule::removeGun()
{}

void WeaponModule::handleEvent(SDL_Event& e)
{
	//ammo->handleEvent(e);

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
	//ammo->onBeforeRender();

	if (isOnCooldown && cooldownTimer.getTicks() > cooldownMs)
	{
		isOnCooldown = false;
		cooldownTimer.stop();
	}
}

void WeaponModule::onAfterRender()
{
	//ammo->onAfterRender();
}

WeaponModule::~WeaponModule()
{
	ship = NULL;
	delete ammo;
	ammo = NULL;
	system = NULL;
}

