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
	{ 2000, PIRATE_A }, 
	{ 3000, PIRATE_A },
	{ 5000, PIRATE_A },
	{ 10000, PIRATE_A },
	{ 12000, PIRATE_A },
	{ 15000, BOSS_A },
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
// - buff description (as option for the pause menu)
// - control description (as option for the pause menu)
// - switch complexity (settings option)
// - enemy ships
// - more enemy flying trace with adapting path
// - switch weapon mechanics

// To Refactor:
// - replace for sdl
// - some design pattern improvements
// - other todos