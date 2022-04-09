#pragma once
#include <SDL.h>
#include <vector>

#include "App.h"
#include "LevelBase.h"
#include "LevelManager.h"
#include "Object.h"

class Level1 : public LevelBase {
private:
	LevelManager* controller;
	void initAudio();
public: 
	Level1(const App* p_system, LevelManager* p_controller) :
		LevelBase(p_system, p_controller) {};

	virtual void load();
};

// Todo: 
// 1. Select ship before the game; ship should has params as [ health, armour, speed, weapon, buffs ]
// 2. Show dialog with the task description at the begining. Implement dialog panel
// ---> 3. Create pause menu view and mechanism to stop the level
// 4. Hood should have: [ health, armour, buffs, score, weapon ]
// 5. Add joystick support
// --> 6. 2 players game support (Todo: add one more item to main menu)
// 7. Fullscreen mode
// 8. Russian language
// --> 9. File saving progress and settings
// 10. More [ player ships, enemies, weapons, buffs, bosses, enemies behaviour logic ]
// 11. Score at the end of the level with achieved weapon
// ---> 12. Ship collision box
// 13. Game over panel w/ try again button and score
// 14. Add directional ship moving with GPS system
// 15. Current goals system
// 16. Increase windowed screen size;

// Current goal - some refactoring and implement #14