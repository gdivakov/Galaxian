#pragma once
#include <iostream>

#include "EnemyShip.h"
#include "LevelBase.h"
#include "ShipConsts.h"

const enum GUN_POS { BOSS_GUN_LEFT, BOSS_GUN_RIGHT, BOSS_GUN_CENTER };

class BossShip : public EnemyShip
{
public:
	BossShip(
        LevelBase* p_level,
        ShipType type,
        Ship* playerShip
    );
    void onBeforeRender();
private:
    void updateGunPos(GUN_POS nextPos);
    void amplify();
    GUN_POS selectedPos;
};