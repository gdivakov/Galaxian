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
struct PJ_Textures { Texture* flying; Texture* launch; Texture* explosion; };

class ProjectileManager
{
public:
	ProjectileManager(GunType p_type, const App* p_system, Ship* p_ship);
	~ProjectileManager();
	void startProjectile();
	void destroyProjectile(Projectile* pj);
private:
	typedef std::vector<SDL_Rect*> ClipPointers;
	typedef std::vector<Projectile*> FlyingProjectiles;

	PJ_Textures textures;
	FlyingProjectiles releasedPjs;
	GunType gunType;
	Ship* ship;
	const App* system;
};