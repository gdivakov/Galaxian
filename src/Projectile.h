#pragma once
#include <SDL.h>

#include "Texture.h"
#include "ShipConsts.h"
#include "Ship.h"
#include "FlyingProjectile.h"

class Ship;
struct ShipRect;
struct SpriteParams;
const enum GunType;

// Todo: Refactor
class Projectile : public Texture
{
public: 
	Projectile(GunType p_type, SDL_Renderer* p_renderer, Ship* p_ship);
	void startProjectile();
	void move(FlyingProjectile* pj);

	void virtual handleEvent(SDL_Event& e) {};
	void virtual onBeforeRender();
	void virtual onAfterRender();
private:
	typedef std::vector<SDL_Rect*> ClipPointers;
	typedef std::vector<FlyingProjectile*> FlyingProjectiles;

	Size size;
	int speed;
	FlyingProjectiles releasedPjs;
	ClipPointers explosionClips;
	ClipPointers clips;
	GunType gunType;
	Ship* ship;
};