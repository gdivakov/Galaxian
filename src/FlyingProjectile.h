#pragma once
#include <SDL.h>

#include "Collidable.h"
#include "Vector2.h"

class FlyingProjectile : public Collidable
{
private:
	Vector2 position;
	Vector2 direction;
	int rotation;

	short frame;
	bool isStarted;
public:
	FlyingProjectile(SDL_Renderer* p_renderer, Vector2 position, Vector2 direction, int rotation, GunType gunType);
	//~FlyingProjectile();
	Vector2 getPosition() { return position; };
	void setPosition(Vector2 nextPosition) { position = nextPosition; };
	Vector2 getDirection() { return direction; };
	short getFrame() { return frame; };
	short setFrame(short nextFrame) { frame = nextFrame; return frame; }
	int getRotation() { return rotation; };
	bool getIsStarted() { return isStarted; };
	void setIsStarted(bool nextIsStarted) { isStarted = nextIsStarted; };
	void showColliders() { Collidable::showColliders(); };
	virtual void shiftColliders();
	virtual void handleCollided();
};