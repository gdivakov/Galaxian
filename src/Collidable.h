#pragma once
#include "Consts.h"
#include "ShipConsts.h"

const Colliders DEFAULT_RECT_COLLIDERS = {};

class Collidable
{
public:
	typedef std::vector<Collidable*> Collidables;

	CollidableType type;
	bool isActive;
	Collidables linkedCollidables;

	Collidable(SDL_Renderer* p_renderer, CollidableType p_type, int wrapperRadius, Colliders p_colliders = DEFAULT_RECT_COLLIDERS);
	virtual ~Collidable();
	virtual void handleCollided() = 0;
	void linkTo(Collidable* enColl); // Todo: rename by linkWith
	void unlinkFrom(); // Todo: rename by unlink
	bool checkCollision();
private:
	Colliders colliders; // Rect colliders
	SDL_Renderer* renderer;
	
	bool checkRectCollision(Collidable* enemyCollider);
protected:
	Collidable* collidedTo;
	bool isCollided;
	int rotation;
	Circle wrapperCollider; // Circle wrapper collider

	void showColliders();
	Colliders getColliders() { return colliders; };
	virtual void shiftColliders() = 0;
	virtual void destroyCollidable() = 0;
};