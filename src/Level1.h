#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"
#include "Object.h"
#include "EnemyShip.h"
#include "DynamicBackground.h"

// To Refactor:
// - some design pattern improvements

struct NextEnemy
{
	const int milesToSpawn;
	const ShipType type;
};

const std::vector<NextEnemy> SPAWNED_ENEMIES 
{ 
	// wave 1
	{ 1000, PIRATE_C }, 
	{ 1500, PIRATE_C },
	{ 2000, PIRATE_C },
	{ 2500, PIRATE_C },
	{ 3000, PIRATE_C },
	{ 3500, PIRATE_C },
	// wave 2
	{ 13000, PIRATE_E },
	{ 14000, PIRATE_F },
	{ 15000, PIRATE_B },
	{ 19000, PIRATE_B },
	{ 20500, PIRATE_A },
	{ 21900, PIRATE_A },
	// wave 3
	{ 25500, PIRATE_D },
	{ 27900, PIRATE_D },
	{ 28000, PIRATE_D },
	{ 29500, PIRATE_F },
	{ 31900, PIRATE_F },
	{ 33000, PIRATE_F },
	// wave 4
	{ 40900, PIRATE_E },
	{ 44000, PIRATE_E },
	{ 46900, PIRATE_E },
	{ 48000, PIRATE_B },
	{ 49500, PIRATE_B },
	{ 50000, PIRATE_C },
	{ 53500, PIRATE_C },
	{ 54000, PIRATE_C },
	{ 56500, PIRATE_C },
	// boss
	{ 60000, BOSS_A },
};

class Level1 : public LevelBase {
public:
	Level1(const App* p_system, LevelManager* p_controller);
	~Level1();
	virtual void load();
	virtual void handleTick();
	virtual void handleCompleted();
private:
	const std::vector<NextEnemy> enemiesToSpawn = SPAWNED_ENEMIES;
	void initObjects();
	DynamicBackground* bg;
protected:
	virtual void initAudio();
};