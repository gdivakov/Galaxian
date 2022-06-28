#pragma once
#include "Vector2.h"
#include "ShipConsts.h"

const Vector2 gunPos1(-47, 40);
const Vector2 gunPos2(47, 40);
const Vector2 gunPos3(0, 40);

const SpriteParams diffuserBossSprite = { "res/sprites/ships/bossAdiffuser.png", 300, 195, 10 };
const SpriteParams doubledBossSprite = { "res/sprites/ships/bossAdoubled.png", 300, 195, 10 };

const float DOUBLE_ROCKET_ARM_THRESHOLD = 0.6;
const float DIFFUSER_ARM_THRESHOLD = 0.1;

const enum BOSS_GUN_POS { BOSS_GUN_LEFT, BOSS_GUN_RIGHT, BOSS_GUN_CENTER };

const std::vector<BezierCurve> BOSS_PATH_A =
{
	{ Vector2(50, 10), Vector2(150, 60), Vector2(200, 160), Vector2(250, 260) },
	{ Vector2(250, 260), Vector2(300, 300), Vector2(400, 300), Vector2(600, 320) },
	{ Vector2(600, 320), Vector2(650, 300), Vector2(750, 200), Vector2(800, 100) },
	{ Vector2(800, 100), Vector2(600, 200), Vector2(500, 210), Vector2(300, 160) },
};
const std::vector<BezierCurve> BOSS_PATH_B =
{
	{ Vector2(100, 10), Vector2(350, 60), Vector2(350, 160), Vector2(300, 260) },
	{ Vector2(300, 260), Vector2(600, 700), Vector2(500, 300), Vector2(600, 600) },
	{ Vector2(600, 600), Vector2(400, 200), Vector2(100, 100), Vector2(500, 300) },
};
const std::vector<BezierCurve> BOSS_PATH_C =
{
	{ Vector2(500, 300), Vector2(450, 200), Vector2(800, 160), Vector2(850, 260) },
	{ Vector2(800, 260), Vector2(700, 300), Vector2(650, 400), Vector2(500, 500) },
	{ Vector2(400, 100), Vector2(350, 200), Vector2(300, 150), Vector2(50, 200) },
};