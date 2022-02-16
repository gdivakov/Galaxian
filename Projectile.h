#pragma once
#include <SDL.h>

#include "Texture.h"
//#include "Consts.h"

struct TextureParams;
const enum GunTypes;

struct FlyingProjectile
{
	SDL_Point position;
	short frame;
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
	int width, height;
	int vel;
	std::vector<FlyingProjectile>releasedPjs;
	GunTypes gunType;
};