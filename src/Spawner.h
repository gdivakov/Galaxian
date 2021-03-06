#pragma once
#include <SDL.h>

#include "Object.h"
#include "LevelBase.h"
#include "Ship.h"
#include "BuffView.h"

class LevelBase;
class EnemyShip;
class BuffView;
class Ship;

class Spawner : public Object
{
public:
	Spawner(LevelBase* p_level);
	~Spawner();

	virtual void onBeforeRender();
	virtual void onAfterRender();
	virtual void handleEvent(SDL_Event& e);

	Ship* getPlayer() { return player; };
	std::vector<Ship*> getEnemies() { return enemies; };
	void removeObject(Object* object);
	void spawnEnemy(ShipType type);
	void spawnPlayer();
	void spawnBuffWithChance(Vector2 buffPos);
	void accelerate();
	void stopAcceleration();
	void setIsBuffSpawn(bool nextIsSpawn) { isBuffsSpawnEnabled = nextIsSpawn; };
	int getSpawnedEnemiesCount() { return spawnedEnemiesCount; };
private:
	static int spawnedEnemiesCount;
	LevelBase* level;

	Ship* player = NULL;
	std::vector<Ship*> enemies;
	std::vector<BuffView*> buffs;
	bool isBuffsSpawnEnabled;
};