#pragma once
#include <iostream>

#include "EnemyShip.h"
#include "LevelBase.h"
#include "ShipConsts.h"
#include "BossConsts.h"

class BossShip : public EnemyShip
{
public:
	BossShip(
        LevelBase* p_level,
        ShipType type
    );
    void onBeforeRender();
private:
    void updateGunPos(BOSS_GUN_POS nextPos);
    void amplify();
    BOSS_GUN_POS selectedPos;
};