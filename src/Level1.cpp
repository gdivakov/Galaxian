#include <iostream>
#include <SDL.h>

#include "Level1.h"
#include "Ship.h"

#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Background.h"
#include "Consts.h"
#include "Hood.h"

ShipParams getShipParams(const Size* windowSize, const ShipType type);
std::vector<BezierCurve> getEnemyPathCurves();

//std::vector<SDL_Rect> SONIC_A_COLLIDERS = { { 0, 0, 29, 31 }, { 0, 0, 102, 51 } };
//std::vector<SDL_Rect> PIRATE_A_COLLIDERS = { { 0, 0, 17, 43 }, { 0, 0, 65, 57 } };

std::vector<RectColliderPoint> SONIC_A_COLLIDERS_DEFAULT =
{
	{
		Vector2(-15, -15-40),
		Vector2(15, -15-40),
		Vector2(15, 15-40),
		Vector2(-15, 15-40),
	},
	{
		Vector2(-50, -25),
		Vector2(50, -25),
		Vector2(50, 25),
		Vector2(-50, 25),
	}
};

std::vector<RectColliderPoint> PIRATE_A_COLLIDERS_DEFAULT =
{
	{
		Vector2(-9, -21-50),
		Vector2(9, -21-50),
		Vector2(9, 21-50),
		Vector2(-9, 21-50),
	},
	{
		Vector2(-32, -28),
		Vector2(32, -28),
		Vector2(32, 28),
		Vector2(-32, 28),
	}
};

// Todo: 
// 1. Select ship before the game; ship should has params as [ health, armour, speed, weapon, buffs ]
// 2. Show dialog with the task description at the begining
// ---> 3. Create pause menu view and mechanism to stop the level
// 4. Hood should have: [ health, armour, buffs, score, weapon ]
// 5. Add joystick support
// 6. 2 players game support 
// 7. Fullscreen mode
// 8. Russian language
// ---> 9. File saving progress and settings
// 10. More [ player ships, enemies, weapons, buffs, bosses, enemies behaviour logic ]
// 11. Score at the end of the level with achieved weapon
// ---> 12. Ship collision box

void Level1::load() 
{
	ShipParams sonicParams = getShipParams(system->getWindowSize(), SONIC_A);
	ShipParams pirateParams = getShipParams(system->getWindowSize(), PIRATE_A);

	Background* backgroundLvl1 = new Background(renderer, "res/space.png", this);
	Hood* hood = new Hood(renderer, this, system);

	EnemyShip* pirate = new EnemyShip(
		system,
		this,
		pirateParams,
		//playerShip,
		getEnemyPathCurves()
	);

	PlayerShip* playerShip = new PlayerShip(
		system, 
		this, 
		sonicParams,
		pirate
	);

	//playerShip.loadCollider();
	//playerShip.removeCollider();

	// Prepare level audio
	Audio* audioPlayer = system->getAudioPlayer();
	audioPlayer->loadMusic("res/lvl1.mp3");
	audioPlayer->playMusic(); 

	eventListeners = { backgroundLvl1, playerShip, audioPlayer, pirate, hood };
	renderListeners = { backgroundLvl1, playerShip, pirate, hood };
	objsToFree = { backgroundLvl1, playerShip, pirate, hood };

	registerListeners();
}

ShipParams getShipParams(const Size* windowSize, const ShipType type)
{
	switch (type)
	{
		case SONIC_A:
			return { SONIC_A_SHIP, ROCKET, SONIC_A_SPEED, SONIC_A_COLLIDERS_DEFAULT };
		case PIRATE_A:
			return { PIRATE_A_SHIP, ROCKET, PIRATE_A_SPEED, PIRATE_A_COLLIDERS_DEFAULT };
	}
}

std::vector<BezierCurve> getEnemyPathCurves()
{
	std::vector<BezierCurve> curves;

	curves.push_back({ Vector2(100, 10), Vector2(350, 60), Vector2(350, 160), Vector2(300, 260) });
	curves.push_back({ Vector2(300, 260), Vector2(600, 700), Vector2(500, 300), Vector2(600, 600) });
	//curves.push_back({ Vector2(600, 600), Vector2(400, 200), Vector2(100, 100), Vector2(500, 300) });

	return curves;
}