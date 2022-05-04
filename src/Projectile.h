#pragma once
#include <SDL.h>

#include "Collidable.h"
#include "Vector2.h"
#include "Ship.h"
#include "Object.h"
#include "Texture.h"
#include "ProjectileManager.h"
#include "App.h"
#include "Consts.h"

class Ship;
class ProjectileManager;
struct PJ_Textures;

class Projectile : public Collidable, public Object
{
private:
	Vector2 position;
	Vector2 direction;
	int rotation;
	int speed;

	PJ_Textures& textures;
	Texture* selectedTexture;

	short frame;
	bool isStarted;
	Ship* ship;
	const App* system;
	ProjectileManager* parent;

	void move();
public:
	Projectile(
		const App* p_system,
		Vector2 initPosition,
		Ship* p_ship,
		GunType gunType,
		int p_speed,
		PJ_Textures& p_textures,
		ProjectileManager* p_parent
	);
	~Projectile();
	void showColliders() { Collidable::showColliders(); };
	virtual void shiftColliders();
	virtual void handleCollided();
	virtual void destroyCollidable();
	virtual void handleEvent(SDL_Event& e) {};
	virtual void onBeforeRender();
	virtual void onAfterRender();
};