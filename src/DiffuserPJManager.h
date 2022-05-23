#pragma once
#include "ProjectileManager.h"
#include "ShipConsts.h"
#include "App.h"
#include "Ship.h"

class DiffuserPJManager : public ProjectileManager
{
public:
	DiffuserPJManager(GunType type, const App* system, Ship* ship)
		: ProjectileManager(type, system, ship) {};
	virtual void startProjectile();
private:
	PJ_Params getParamsByAngle(int angle);
};

