#pragma once
#include "Consts.h"
#include "ShipConsts.h"

// Collidable contains wrapper & rectangle colliders
class Collidable
{
public:
	Collidable(SDL_Renderer* p_renderer, Colliders p_colliders, int wrapperRadius);
	virtual ~Collidable() {};
	void registerEnemyCollider(Collidable* enemyCollider) { enemyColliders.push_back(enemyCollider); };
	void deregisterEnemyCollider(Collidable* enemyCollider);
private:
	Colliders colliders;
	std::vector<Collidable*> enemyColliders;
	SDL_Renderer* collidableRenderer;
	bool checkRectCollision(Collidable* enemyCollider);
protected:
	int collidableRotation;
	Circle wrapperCollider;
	void showColliders();
	bool checkCollision();
	virtual void shiftColliders() = 0;
	virtual void handleCollided() = 0;
	Colliders getColliders() { return colliders; };
};

