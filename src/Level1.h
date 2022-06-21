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

class Level1 : public LevelBase {
public:
	Level1(const App* p_system, LevelManager* p_controller);
	~Level1();
	virtual void load();
	virtual void accelerate();
	virtual void handleTick();
private:
	const std::vector<NextEnemy> enemiesToSpawn { 
		{ 2000, PIRATE_A }, 
		//{ 2000, PIRATE_A },
		{ 15000, PIRATE_A },
		//{ 15000, PIRATE_A },
		//{ 20000, PIRATE_A },
		//{ 20000, PIRATE_A },

		//{ 20000, BOSS_A },
	};

	void initObjects();
	DynamicBackground* bg;
protected:
	virtual void initAudio();
};

// Todo: 
// 1. ->>Select ship before the game; ship should has params as [ health, armour, speed, weapon, buffs ]
// 2. Show dialog with the task description at the begining. Implement dialog panel
// ---> 3. Create pause menu view and mechanism to stop the level
// ---> 4. Hood should have: [ health, armour, buffs, score, weapon ]
// 5. Add joystick support
// --> 6. 2 players game support (Todo: add one more item to main menu)
// 7. Fullscreen mode
// 8. Russian language
// --> 9. File saving progress and settings
// 10. More [ player ships, enemies, weapons, buffs, bosses, enemies behaviour logic ]
// 11. Score at the end of the level with achieved weapon
// ---> 12. Ship collision box
// 13. Game over panel w/ try again button and score
// 16. Increase windowed screen size;
// 17. Add meteors