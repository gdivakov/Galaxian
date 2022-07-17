#include "DoublePJManager.h"

void DoublePJManager::startProjectile()
{
	AmmoParams ammoParams = AMMO_PARAMS.at(gunType);
	// In order to display double rocket correctly gunPos must differs from 0
	Vector2 gunPos = ship->getGun()->getGunPos();

	Vector2 position = ship->getDirection(LOCAL, false) - Vector2(0, textures.launch->size.h / 2) + gunPos;
	position = Vector2::getRotatedVector(position, ship->getRotation()) + ship->getRect().pos;

	PJ_Params leftPJParams = {
		position,
		gunType,
		ammoParams.speed,
		ship->getDirection(LOCAL, false),
		ship->getRotation(),
		textures,
	};

	Vector2 position2 = ship->getDirection(LOCAL, false) - Vector2(0, textures.launch->size.h / 2) + Vector2(0, gunPos.y) - Vector2(gunPos.x, 0);
	position2 = Vector2::getRotatedVector(position2, ship->getRotation()) + ship->getRect().pos;

	PJ_Params rightPJParams = {
		position2,
		gunType,
		ammoParams.speed,
		ship->getDirection(LOCAL, false),
		ship->getRotation(),
		textures,
	};

	releasedPjs.push_back(new Projectile(leftPJParams, this));
	releasedPjs.push_back(new Projectile(rightPJParams, this));
}