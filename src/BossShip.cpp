#include "BossShip.h"
#include "BossShipConsts.h"

// Todo: Boss should drop one of his weapons (double rocket or diffuser)
// Todo: Speed up level to finish the level
// Todo: Spawn some enemies when boss health is low and at the beginning of the fight
// Todo: Add different sounds and PJ sprites to boss
BossShip::BossShip(
    LevelBase* p_level,
    ShipType type,
    Ship* playerShip
) : EnemyShip(p_level, type, playerShip, BOSS_PATH_A)
{
	rotation = 180;
	updateGunPos(BOSS_GUN_LEFT);
	level->spawner->setIsBuffSpawn(false);
}

void BossShip::amplify()
{
	float armor = specials.status->getArmor();
	float maxArmor = specials.status->getMaxArmor();
	float threshold = armor / maxArmor;

	if (threshold <= DIFFUSER_ARM_THRESHOLD)
	{
		if (gun->getSelectedGun() == DIFFUSER)
		{
			return;
		}

		updateGunPos(BOSS_GUN_CENTER);
		gun->selectGun(DIFFUSER); // Select diffuser gun

		loadFromSprite(diffuserBossSprite); // Load ship sprites for diffuser gun
		addPath(BOSS_PATH_C); // Add new path
		setMaxSpeed(maxSpeed * 2); // Accelerate ship
		return;
	}

	if (threshold <= DOUBLE_ROCKET_ARM_THRESHOLD && gun->getSelectedGun() != ROCKET_DOUBLE)
	{
		updateGunPos(BOSS_GUN_LEFT);
		gun->selectGun(ROCKET_DOUBLE);

		loadFromSprite(doubledBossSprite);
		addPath(BOSS_PATH_B);
		return;
	}
}

void BossShip::onBeforeRender()
{
	gun->onBeforeRender();
	amplify();

	if (!level->isPaused)
	{
		if (isActive)
		{
			followPath(false);
			move();
		}

		if (isInView() && isActive)
		{
			gun->isShooting = true;

			if (selectedPos != BOSS_GUN_CENTER)
			{
				updateGunPos(selectedPos == BOSS_GUN_LEFT ? BOSS_GUN_RIGHT : BOSS_GUN_LEFT);
			}
		}
		else
		{
			gun->isShooting = false;
		}
	}

	std::vector<SDL_Rect>& shipClips = getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

	render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
	//displayPath();
}

void BossShip::updateGunPos(GUN_POS nextPos)
{
	selectedPos = nextPos;

	switch (nextPos)
	{
	case BOSS_GUN_CENTER:
		return getGun()->setGunPos(gunPos3);
	case BOSS_GUN_LEFT:
		return getGun()->setGunPos(gunPos1);
	case BOSS_GUN_RIGHT:
		return getGun()->setGunPos(gunPos2);
	}
}