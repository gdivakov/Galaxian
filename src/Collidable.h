#pragma once
#include "Consts.h"
#include "ShipConsts.h"

// Collidable contains wrapper & rectangle colliders
class Collidable
{
public:
	Collidable(SDL_Renderer* p_renderer, Colliders p_colliders, int wrapperRadius);
	virtual ~Collidable();
	std::vector<Collidable*> getEnemyCollidables() { return enemyCollidables; };
	void registerEnemyCollidable(Collidable* enemyCollidable);
	bool checkCollision();
	bool getIsCollided() { return isCollided; };
	virtual void handleCollided() = 0;
	Collidable* getCollidedTo() { return collidedTo; };
	void deregisterEnemyCollidable(Collidable* enemyCollidable);
private:
	Colliders colliders;
	std::vector<Collidable*> enemyCollidables;
	SDL_Renderer* collidableRenderer;
	bool checkRectCollision(Collidable* enemyCollider);
protected:
	Collidable* collidedTo;
	bool isCollided;
	int collidableRotation;
	Circle wrapperCollider;
	void showColliders();
	virtual void shiftColliders() = 0;
	Colliders getColliders() { return colliders; };
};

