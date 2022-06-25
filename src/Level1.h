#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"
#include "Object.h"
#include "EnemyShip.h"
#include "DynamicBackground.h"

struct NextEnemy
{
	const int milesToSpawn;
	const ShipType type;
};

const std::vector<NextEnemy> SPAWNED_ENEMIES 
{ 
	//{ 2000, PIRATE_A }, 
	//{ 3000, PIRATE_A },
	//{ 5000, PIRATE_A },
	//{ 10000, PIRATE_A },
	//{ 12000, PIRATE_A },
	//{ 2000, BOSS_A },
};

class Level1 : public LevelBase {
public:
	Level1(const App* p_system, LevelManager* p_controller);
	~Level1();
	virtual void load();
	virtual void accelerate();
	virtual void handleTick();
	virtual void handleCompleted();
private:
	const std::vector<NextEnemy> enemiesToSpawn = SPAWNED_ENEMIES;
	void initObjects();
	DynamicBackground* bg;
protected:
	virtual void initAudio();
};

// To Add: 
// - meteors
// - enemy ships
// - more enemy flying trace
// - show "ship upgrade available" on totalView; 

// To Refactor:
// - replace for stl
// - save progress when player reaches the boss
// - some design pattern improvements
// - other todos