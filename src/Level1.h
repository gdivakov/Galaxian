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
	//{ 1000, PIRATE_C }, 
	//{ 1500, PIRATE_C },
	//{ 2000, PIRATE_C },
	//{ 2500, PIRATE_C },
	//{ 3000, PIRATE_C },
	//{ 3500, PIRATE_C },

	//{ 15000, PIRATE_E },
	//{ 15500, PIRATE_F },
	{ 16000, PIRATE_B },

	//{ 16600, BOSS_A },
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

// To Add: 
// - meteors
// - update hit animation
// - make only one gun available for hard mode
// - flying pj should not be removed when gun changed
// - center the preview ship image on totalView

// To Refactor:
// - replace for stl
// - save progress when player reaches the boss
// - some design pattern improvements
// - other todos