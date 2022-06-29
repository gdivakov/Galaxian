#pragma once 

#include <iostream>
#include <vector>

#include "Timer.h"
#include "ProjectileManager.h"
#include "Consts.h"
#include "Ship.h"
#include "App.h"
#include "Vector2.h"

class Ship;
class ProjectileManager;

class WeaponModule
{
public:
	WeaponModule(
		std::vector<GunType> guns, 
		const App* p_system,
		Ship* p_ship
	);
	~WeaponModule();

	Vector2 getGunPos() { return pos; };
	void setGunPos(Vector2 nextPos) { pos = nextPos; }
	bool getIsShooting() { return isShooting; };
	void setIsShooting(bool nextIsShooting) { isShooting = nextIsShooting; }

	void selectGun(GunType nextGun);
	GunType selectNextGun();
	GunType getSelectedGun() { return type; };

	void handleRender();
private:
	const App* system;
	Ship* ship;

	Vector2 pos; // Relative pos
	GunType type;
	std::map<SUPPORTED_PJ_MANAGERS, ProjectileManager*> ammo;
	std::vector<GunType> installedGuns;

	Timer* cooldownTimer;
	bool isShootStarted;
	bool isShooting;
	bool isOnCooldown;
};