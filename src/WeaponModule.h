#pragma once 

#include <iostream>
#include <vector>

#include "Timer.h"
#include "ProjectileManager.h"
#include "Consts.h"
#include "Ship.h"
#include "App.h"

class Ship;
class ProjectileManager;

// Todo: refactor
class WeaponModule : public Texture
{
public:
	WeaponModule(
		GunType initGunType, 
		const App* p_system,
		Ship* p_ship,
		bool p_isEnemyShip
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
	//std::vector<GunType> availableGuns;
	Timer cooldownTimer;
	Ship* ship;
	ProjectileManager* ammo;
	const App* system;
	bool isEnemyShip;
	std::string fireSound;
};