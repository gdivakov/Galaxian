#include "Ship.h"
#include "ShipConsts.h"

WeaponModule::WeaponModule(
	GunType initGunType,
	const App* p_system,
	Ship* p_ship
) : Texture(p_system->getRenderer()), system(p_system)
{
	ammo = new Projectile(initGunType, system->getRenderer(), p_ship);
	ship = p_ship;
	isOnCooldown = false;

	// Prepare gun
	GunParams params = getGunParamsByType(initGunType);
	cooldownMs = params.cooldownMs;

	availableGuns.push_back(initGunType);
	selectedGun = availableGuns[0];
	fireSoundId = system->getAudioPlayer()->loadSound(params.soundPath);
}

void WeaponModule::fire()
{
	if (isOnCooldown)
	{
		return;
	}

	system->getAudioPlayer()->playSound(fireSoundId);
	ammo->startProjectile();


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
	ammo->handleEvent(e);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	// Todo: Fix issue with left+top+l pressed
	if (currentKeyStates[SDL_SCANCODE_L])
	{
		fire();
		return;
	}
}
void WeaponModule::onBeforeRender()
{
	ammo->onBeforeRender();

	if (isOnCooldown && cooldownTimer.getTicks() > cooldownMs)
	{
		isOnCooldown = false;
		cooldownTimer.stop();
	}
}

void WeaponModule::onAfterRender()
{
	ammo->onAfterRender();
}

WeaponModule::~WeaponModule()
{
	ship = NULL;
	delete ammo;
	ammo = NULL;
	system = NULL;
}

