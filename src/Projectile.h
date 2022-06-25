#pragma once
#include <SDL.h>

#include "Collidable.h"
#include "Vector2.h"
#include "Object.h"
#include "Texture.h"
#include "ProjectileManager.h"
#include "Consts.h"
#include "ShipConsts.h"

class Ship;
class ProjectileManager;

// Todo: pj should not be deleted after the weapon switch
class Projectile : public Collidable, public Object
{
private:
	Vector2 position;
	Vector2 direction;
	int rotation;
	int speed;

	PJ_Textures textures;
	Texture* selectedTexture;

	short frame;
	bool isStarted;
	ProjectileManager* parent;

	void move();
	void resetAnimation() { frame = 0; };
	void selectTexture();
	Vector2 getNextPos();
public:
	Projectile(PJ_Params params, ProjectileManager* p_parent);
	~Projectile();
	void showColliders() { Collidable::showColliders(); };
	virtual void shiftColliders();
	virtual void handleCollided();
	virtual void destroyCollidable();
	virtual void handleEvent(SDL_Event& e) {};
	virtual void onBeforeRender();
	virtual void onAfterRender();
};