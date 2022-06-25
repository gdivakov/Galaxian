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

// Todo: refactor
class WeaponModule : public Texture
{
public:
	WeaponModule(
		std::vector<GunType> guns, 
		const App* p_system,
		Ship* p_ship,
		bool p_isEnemyShip
	);
	~WeaponModule();

	void selectGun(GunType nextGun);
	GunType selectNextGun();
	Vector2 getGunPos() { return pos; };
	void setGunPos(Vector2 nextPos) { pos = nextPos; }
	GunType getSelectedGun() { return selectedGun; };
	bool getIsShooting() { return isShooting; };
	void setIsShooting(bool nextIsShooting) { isShooting = nextIsShooting; }
	void handleRender();
private:
	bool isOnCooldown;
	float cooldownMs;
	short fireSoundId;
	GunType selectedGun;
	Timer cooldownTimer;
	Ship* ship;
	ProjectileManager* ammo;
	const App* system;
	bool isEnemyShip;
	std::string fireSound;
	Vector2 pos; // Relative pos
	bool isShootStarted = false;
	bool isShooting;
	std::vector<GunType> installedGuns;
};