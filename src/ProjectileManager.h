#pragma once
#include <SDL.h>

#include "ShipConsts.h"
#include "Ship.h"
#include "Projectile.h"
#include "Texture.h"
#include "App.h"

class Ship;
struct ShipRect;
struct SpriteParams;
const enum GunType;
class Projectile;

class ProjectileManager
{
public:
	ProjectileManager(GunType p_type, const App* p_system, Ship* p_ship);
	virtual ~ProjectileManager();

	virtual void startProjectile() = 0;
	void destroyProjectile(Projectile* pj);
	Ship* getShip() { return ship; };
	const App* getSystem() { return system; };
protected:
	typedef std::vector<SDL_Rect*> ClipPointers;
	typedef std::vector<Projectile*> FlyingProjectiles;

	PJ_Textures textures;
	FlyingProjectiles releasedPjs;
	GunType gunType;
	Ship* ship;
	const App* system;
};