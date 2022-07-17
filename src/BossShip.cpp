#include "BossShip.h"
// Todo: Spawn some enemies when boss health is low and at the beginning of the fight
// Todo: Add different sounds and PJs to boss

BossShip::BossShip(
    LevelBase* p_level,
    ShipType type
) : EnemyShip(p_level, type, BOSS_PATH_A)
{
	rotation = 180;
	selectedPos = BOSS_GUN_RIGHT;

	toggleRocketGunPos();
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

		gun->selectGun(ROCKET_DIFFUSER); // Select diffuser gun

		getTexture()->loadFromSprite(diffuserBossSprite); // Load ship sprites for diffuser gun
		addPath(BOSS_PATH_C); // Add new path
		setMaxSpeed(maxSpeed * 2); // Accelerate ship
		return;
	}

	if (threshold <= DOUBLE_ROCKET_ARM_THRESHOLD && gun->getSelectedGun() != ROCKET_DOUBLE)
	{
		gun->selectGun(ROCKET_DOUBLE);

		getTexture()->loadFromSprite(doubledBossSprite);
		addPath(BOSS_PATH_B);
		return;
	}
}

void BossShip::handleActions()
{
	if (level->isPaused)
	{
		return;
	}

	// Move 
	if (isActive)
	{
		followPath(false);
		move();
	}

	// Shoot at player
	if (isPlayerInView() && isActive)
	{
		gun->setIsShooting(true);

		if (gun->getSelectedGun() == ROCKET)
		{
			// Manual update pos for ROCKET in order to alternate left and right guns
			toggleRocketGunPos();
		}
		return;
	}

	gun->setIsShooting(false);
}

void BossShip::onBeforeRender()
{
	gun->handleRender();
	amplify();

	handleActions();

	std::vector<SDL_Rect>& shipClips = getTexture()->getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
	Size& size = getTexture()->size;

	getTexture()->render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
}

void BossShip::toggleRocketGunPos()
{
	selectedPos = selectedPos == BOSS_GUN_LEFT ? BOSS_GUN_RIGHT : BOSS_GUN_LEFT;

	switch (selectedPos)
	{
	case BOSS_GUN_LEFT:
		return getGun()->setGunPos(BOSS_DOUBLE_GUN_POS);
	case BOSS_GUN_RIGHT:
		return getGun()->setGunPos(Vector2(BOSS_DOUBLE_GUN_POS.x * -1, BOSS_DOUBLE_GUN_POS.y));
	}
}