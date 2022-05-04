#pragma once
#include "Consts.h"
#include "ShipConsts.h"

// Collidable contains wrapper & rectangle colliders
class Collidable
{
public:
	Collidable(SDL_Renderer* p_renderer, Colliders p_colliders, CollidableType p_type, int wrapperRadius);
	virtual ~Collidable() {};
	std::vector<Collidable*> getEnemyCollidables() { return enemyCollidables; };
	void registerEnemyCollidable(Collidable* enemyCollidable);
	bool checkCollision();
	bool getIsCollided() { return isCollided; };
	virtual void handleCollided() = 0;
	Collidable* getCollidedTo() { return collidedTo; };
	void deregisterEnemyCollidable(Collidable* enemyCollidable);
	CollidableType getCollidableType() { return type; };
	bool getIsActive() { return isActive; };
	bool setIsActive(bool nextIsActive) { return isActive = nextIsActive; }
private:
	Colliders colliders;
	std::vector<Collidable*> enemyCollidables;
	SDL_Renderer* collidableRenderer;
	bool checkRectCollision(Collidable* enemyCollider);
	CollidableType type;
protected:
	Collidable* collidedTo;
	bool isCollided;
	bool isActive = true;
	int collidableRotation;
	Circle wrapperCollider;
	void showColliders();
	Colliders getColliders() { return colliders; };
	virtual void shiftColliders() = 0;
	virtual void destroyCollidable() = 0;
};

