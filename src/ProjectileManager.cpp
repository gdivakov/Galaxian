#include <iostream>

#include "ProjectileManager.h"
#include "Vector2.h"

ProjectileManager::ProjectileManager(GunType p_type, const App* p_system, Ship* p_ship)
{	
	AmmoParams params = getAmmoParamsByGunType(p_type);

	ship = p_ship;
	system = p_system;
	gunType = p_type;

	// Load ammo textures
	textures = 
	{
		new Texture(system->getRenderer()),
		new Texture(system->getRenderer()),
		new Texture(system->getRenderer())
	};

	textures.flying->loadFromSprite(params.texture);
	textures.launch->loadFromSprite(params.launchTexture);
	textures.explosion->loadFromSprite(params.explosionTexture);
}

ProjectileManager::~ProjectileManager()
{
	for (int i = 0; i < releasedPjs.size(); i++)
	{
		releasedPjs[i]->destroyCollidable();
		delete releasedPjs[i];
	}

	releasedPjs.clear();

	delete textures.flying;
	delete textures.launch;
	delete textures.explosion;

	textures.flying = NULL;
	textures.launch = NULL;
	textures.explosion = NULL;
	system = NULL;
	ship = NULL;
}

void ProjectileManager::destroyProjectile(Projectile* pj)
{
	auto removeIter = remove(releasedPjs.begin(), releasedPjs.end(), pj);
	releasedPjs.erase(removeIter, releasedPjs.end());

	delete pj;
}