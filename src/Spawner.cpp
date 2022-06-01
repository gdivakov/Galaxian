#include <iostream>

#include "Spawner.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "BossShip.h"
#include "Vector2.h"
#include "ShipSpecialsConsts.h"
#include "SettingsConsts.h"

// Todo: Replace by template func and move to utils
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

void removeFromArray(std::vector<Ship*>& arr, Object* p)
{
	auto removeIter = remove(arr.begin(), arr.end(), p);
	arr.erase(removeIter, arr.end());
}

void removeBuffsFromArray(std::vector<BuffView*>& arr, Object* p)
{
	auto removeIter = remove(arr.begin(), arr.end(), p);
	arr.erase(removeIter, arr.end());
}

Spawner::Spawner(LevelBase* p_level)
{
	level = p_level;
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

	level->handleTick();
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

void Spawner::spawnEnemy()
{
	EnemyShip* nextEnemy = new EnemyShip
	(
		level, 
		PIRATE_A, 
		player, 
		getEnemyPathCurves(enemies.size())
	);

	nextEnemy->linkTo(player);
	enemies.push_back(nextEnemy);
	enemiesSpawned++;
}

void Spawner::spawnBoss()
{
	BossShip* nextBoss = new BossShip(level, BOSS_A, player);

	nextBoss->linkTo(player);
	enemies.push_back(nextBoss);
	enemiesSpawned++;
}

void Spawner::spawnPlayer()
{
	std::vector<int> config = readSettingsConfig();

	ShipType selectedType = (ShipType) config[SELECTED_SHIP_IDX];
	player = new PlayerShip(level, selectedType);
}

void Spawner::spawnBuff(Vector2 buffPos)
{
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
		removeFromArray(enemies, object);
		// Spawn buff w/ some chance
		spawnBuff(enemyShip->getRect().pos);

		delete object;
		return;
	}

	if (instanceof<BuffView>(object))
	{
		removeBuffsFromArray(buffs, object);

		delete object;
		return;
	}
}

void Spawner::accelerateEnemies()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->startAccelerate();
	}

	player->startAccelerate();
}