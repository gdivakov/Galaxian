#pragma once
#include <SDL.h>

#include "Object.h"
#include "LevelBase.h"
#include "Ship.h"
#include "BuffView.h"

class LevelBase;
class EnemyShip;
class BuffView;

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
	void spawnEnemy();
	void spawnPlayer();
	void spawnBuff(Vector2 buffPos);
	void accelerateEnemies();
private:
	LevelBase* level;

	Ship* player = NULL;
	std::vector<Ship*> enemies;
	std::vector<BuffView*> buffs;
};

