#include "BossShip.h"
// Todo: Spawn some enemies when boss health is low and at the beginning of the fight
// Todo: Add different sounds and PJ sprites to boss

BossShip::BossShip(
    LevelBase* p_level,
    ShipType type
) : EnemyShip(p_level, type, BOSS_PATH_A)
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
		if (gun->getSelectedGun() == ROCKET_DIFFUSER)
		{
			return;
		}

		updateGunPos(BOSS_GUN_CENTER);
		gun->selectGun(ROCKET_DIFFUSER); // Select diffuser gun

		getTexture()->loadFromSprite(diffuserBossSprite); // Load ship sprites for diffuser gun
		addPath(BOSS_PATH_C); // Add new path
		setMaxSpeed(maxSpeed * 2); // Accelerate ship
		return;
	}

	if (threshold <= DOUBLE_ROCKET_ARM_THRESHOLD && gun->getSelectedGun() != ROCKET_DOUBLE)
	{
		updateGunPos(BOSS_GUN_LEFT);
		gun->selectGun(ROCKET_DOUBLE);

		getTexture()->loadFromSprite(doubledBossSprite);
		addPath(BOSS_PATH_B);
		return;
	}
}

void BossShip::onBeforeRender()
{
	gun->handleRender();
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
			gun->setIsShooting(true);

			if (selectedPos != BOSS_GUN_CENTER)
			{
				updateGunPos(selectedPos == BOSS_GUN_LEFT ? BOSS_GUN_RIGHT : BOSS_GUN_LEFT);
			}
		}
		else
		{
			gun->setIsShooting(false);
		}
	}

	std::vector<SDL_Rect>& shipClips = getTexture()->getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
	Size& size = getTexture()->size;

	getTexture()->render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
}

void BossShip::updateGunPos(BOSS_GUN_POS nextPos)
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