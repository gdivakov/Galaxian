#include "DiffuserPJManager.h"

PJ_Params DiffuserPJManager::getParamsByAngle(int angle)
{
	AmmoParams ammoParams = AMMO_PARAMS.at(gunType);

	Vector2 position = ship->getDirection(LOCAL, false) - Vector2(0, textures.launch->getHeight() / 2) + ship->getGun()->getGunPos();
	position = Vector2::getRotatedVector(position, ship->getRotation()) + ship->getRect().pos;

	return {
		position,
		gunType,
		ammoParams.speed,
		ship->getDirection(LOCAL, false),
		ship->getRotation() + angle,
		textures,
	};
}

void DiffuserPJManager::startProjectile()
{
	releasedPjs.push_back(new Projectile(getParamsByAngle(0), this));
	releasedPjs.push_back(new Projectile(getParamsByAngle(20), this));
	releasedPjs.push_back(new Projectile(getParamsByAngle(-20), this));
	releasedPjs.push_back(new Projectile(getParamsByAngle(40), this));
	releasedPjs.push_back(new Projectile(getParamsByAngle(-40), this));
}