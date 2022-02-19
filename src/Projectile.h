#pragma once
#include <SDL.h>

#include "Texture.h"
#include "Consts.h"

struct TextureParams;
const enum GunType;

struct FlyingProjectile
{
	SDL_Point position;
	short frame;
	bool isStarted;
};

class Projectile : public Texture // Todo: maybe create class ShipComponent? 
{
public: 
	Projectile(GunType p_type, SDL_Renderer* p_renderer);
	void startProjectile(const SDL_Rect* shipRect);
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
	GunType gunType;
};