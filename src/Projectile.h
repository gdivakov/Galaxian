#pragma once
#include <SDL.h>

#include "Texture.h"
#include "Consts.h"

struct TextureParams;
const enum GunTypes;

struct FlyingProjectile
{
	SDL_Point position;
	short frame;
	bool isStarted;
};

class Projectile : public Texture // Todo: maybe create class ShipComponent? 
{
public: 
	Projectile(GunTypes p_type, SDL_Renderer* p_renderer);
	void startProjectile(SDL_Point* shipPosition);
	void move(FlyingProjectile* pj);

	void virtual handleEvent(SDL_Event& e);
	void virtual onBeforeRender();
	void virtual onAfterRender();
private:
	typedef std::vector<SDL_Rect*> ClipPointers;
	typedef std::vector<FlyingProjectile> FlyingProjectiles;

	int width, height;
	int vel;
	FlyingProjectiles releasedPjs;
	ClipPointers explosionClips;
	ClipPointers clips;
	GunTypes gunType;
};