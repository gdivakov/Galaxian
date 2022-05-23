#pragma once
#include "ProjectileManager.h"
#include "ShipConsts.h"
#include "App.h"
#include "Ship.h"

class SinglePJManager : public ProjectileManager
{
public:
	SinglePJManager(GunType type, const App* system, Ship* ship) 
		: ProjectileManager(type, system, ship) {};
	virtual void startProjectile();
};

