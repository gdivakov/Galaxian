#include "FlyingProjectile.h"

int getRadius(GunType type);

FlyingProjectile::FlyingProjectile(SDL_Renderer* p_renderer, Vector2 p_position, Vector2 p_direction, int p_rotation, GunType gunType)
	: Collidable(p_renderer, getAmmoParamsByGunType(gunType).colliders, getRadius(gunType))
{
	frame = 0;
	rotation = p_rotation;
	position = p_position;
	direction = p_direction;
	isStarted = false;

	shiftColliders();
}

void FlyingProjectile::shiftColliders() {
	wrapperCollider.pos = position;
	collidableRotation = rotation;
};

void FlyingProjectile::handleCollided()
{
	std::cout << "Collided" << std::endl;
}

int getRadius(GunType type)
{
	AmmoParams params = getAmmoParamsByGunType(type);
	return params.texture.imageH > params.texture.imageW ? params.texture.imageH / 2 : params.texture.imageW / 2;
}