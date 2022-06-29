#include <iostream>

#include "Spawner.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "BossShip.h"
#include "Vector2.h"
#include "SpecialsConsts.h"
#include "SettingsConsts.h"
#include "General.h"
#include "Consts.h"

const int BUFF_SPAWN_CHANCE = 35;

int Spawner::spawnedEnemiesCount = 0;

Spawner::Spawner(LevelBase* p_level)
{
	level = p_level;
	isBuffsSpawnEnabled = true;
	spawnedEnemiesCount = 0;
}

Spawner::~Spawner()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}

	for (int i = 0; i < buffs.size(); i++)
	{
		delete buffs[i];
	}

	enemies.clear();
	buffs.clear();

	if (player)
	{
		delete player;
		player = NULL;
	}
}

void Spawner::handleEvent(SDL_Event& e)
{
	if (player)
	{
		player->handleEvent(e);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->handleEvent(e);
	}
}

void Spawner::onBeforeRender()
{
	if (player)
	{
		player->onBeforeRender();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->onBeforeRender();
	}

	for (int i = 0; i < buffs.size(); i++)
	{
		buffs[i]->onBeforeRender();
	}

	level->handleTick();
}

void Spawner::onAfterRender()
{
	if (player)
	{
		player->onAfterRender();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->onAfterRender();
	}

	for (int i = 0; i < buffs.size(); i++)
	{
		buffs[i]->onAfterRender();
	}
}

void Spawner::spawnEnemy(ShipType type)
{
	Ship* nextEnemy;

	switch (type)
	{
	case BOSS_A:
		nextEnemy = new BossShip(level, BOSS_A);
		break;
	default: // Pirate
		nextEnemy = new EnemyShip(level, type, getEnemyPathCurves());
	}

	nextEnemy->linkTo(player);
	enemies.push_back(nextEnemy);
	spawnedEnemiesCount++;
}

void Spawner::spawnPlayer()
{
	std::vector<int> config = readSettingsConfig();

	ShipType selectedType = (ShipType) config[SETTINGS_FIELDS::SELECTED_SHIP];
	player = new PlayerShip(level, selectedType);
}

void Spawner::spawnBuffWithChance(Vector2 buffPos)
{
	int chance = getRandom(100);

	if (chance > BUFF_SPAWN_CHANCE)
	{
		return;
	}

	BuffView* nextBuff = new BuffView(level, buffPos, BUFF_RANDOM);
	buffs.push_back(nextBuff);

	// Link buff with ships
	if (player && player->isActive)
	{
		nextBuff->linkTo(player);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isActive)
		{
			nextBuff->linkTo(enemies[i]);
		}
	}
}

void Spawner::removeObject(Object* object)
{
	if (instanceof<PlayerShip>(object))
	{
		delete object;
		player = NULL;
		return;
	}

	if (instanceof<EnemyShip>(object))
	{
		Ship* enemyShip = (Ship*) object;
		removeFromArray<Ship, Object>(enemies, object);

		// Spawn buff w/ some chance
		if (isBuffsSpawnEnabled)
		{
			spawnBuffWithChance(enemyShip->getRect().pos);
		}

		delete object;
		return;
	}

	if (instanceof<BuffView>(object))
	{
		removeFromArray<BuffView, Object>(buffs, object);

		delete object;
		return;
	}
}

void Spawner::accelerate()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->onAccelerate();
	}

	player->onAccelerate();
}

void Spawner::stopAcceleration()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->onAccelerateEnd();
	}

	player->onAccelerateEnd();
}