#include "SinglePJManager.h"

void SinglePJManager::startProjectile()
{
	AmmoParams ammoParams = AMMO_PARAMS.at(gunType);

	Vector2 gunPos = ship->getGun()->getGunPos();
	Vector2 position = ship->getDirection(LOCAL, false) - Vector2(0, textures.launch->getHeight() / 2) + gunPos;
	position = Vector2::getRotatedVector(position, ship->getRotation()) + ship->getRect().pos;

	PJ_Params PJParams = {
		position,
		gunType,
		ammoParams.speed,
		ship->getDirection(LOCAL, false),
		ship->getRotation(),
		textures,
	};

	releasedPjs.push_back(new Projectile(PJParams, this));
}