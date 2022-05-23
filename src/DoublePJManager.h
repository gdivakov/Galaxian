#pragma once
#include "ProjectileManager.h"
#include "ShipConsts.h"
#include "App.h"
#include "Ship.h"

class DoublePJManager : public ProjectileManager
{
public:
	DoublePJManager(GunType type, const App* system, Ship* ship)
		: ProjectileManager(type, system, ship) {};
	virtual void startProjectile();
};

