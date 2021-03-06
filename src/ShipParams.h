#pragma once
#include "ShipConsts.h"
#include "SoundConst.h"

const Vector2 SONIC_DIFFUSER_GUN_POS(0, 25);
const Vector2 SONIC_DOUBLE_GUN_POS(-10, 0);

const Vector2 BOSS_DOUBLE_GUN_POS(-47, 40);
const Vector2 BOSS_DIFFUSER_GUN_POS(0, 40);

const Vector2 PIRATE_E_DOUBLE_GUN_POS(-30, 0);

const ShipParams SONIC_A_PARAMS =
{
    SONIC_A,
    SONIC_A_SHIP,                               // sprite 
    SONIC_A_SHIP_EXPLOSION,                     // explosion 
    SONIC_A_SHIP_ACCELERATE,                    // accelerate
    { BLAST, BLAST_DOUBLE, BLAST_DIFFUSER },    // gunType 
    SHIP_SPEED_FAST,                            // maxSpeed 
    THIN_SHIP_ARMOR,                            // armor 
    THIN_SHIP_HEALTH,                           // health 
    SONIC_A_COLLIDERS,                          // colliders 
    GAME_OVER_SOUND,                            // explosionSound 
    {                                           // gun positions
        { BLAST_DIFFUSER, SONIC_DIFFUSER_GUN_POS },
        { BLAST_DOUBLE, SONIC_DOUBLE_GUN_POS }
    }
};

const ShipParams SONIC_B_PARAMS =
{
    SONIC_B,
    SONIC_B_SHIP,
    SONIC_B_SHIP_EXPLOSION,
    SONIC_B_SHIP_ACCELERATE,
    { BLAST, BLAST_DOUBLE, BLAST_DIFFUSER },
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    THIN_SHIP_HEALTH,
    SONIC_A_COLLIDERS,
    GAME_OVER_SOUND,
    {
        { BLAST_DIFFUSER, SONIC_DIFFUSER_GUN_POS }, 
        { BLAST_DOUBLE, SONIC_DOUBLE_GUN_POS }
    }
};

const ShipParams SONIC_C_PARAMS =
{
    SONIC_C,
    SONIC_C_SHIP,
    SONIC_C_SHIP_EXPLOSION,
    SONIC_C_SHIP_ACCELERATE,
    { BLAST, BLAST_DOUBLE, BLAST_DIFFUSER},
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    THIN_SHIP_HEALTH,
    SONIC_C_COLLIDERS,
    GAME_OVER_SOUND,
    {
        { BLAST_DIFFUSER, SONIC_DIFFUSER_GUN_POS },
        { BLAST_DOUBLE, SONIC_DOUBLE_GUN_POS }
    }
};

const ShipParams PIRATE_A_PARAMS =
{
    PIRATE_A,
    PIRATE_A_SHIP,
    PIRATE_A_SHIP_EXPLOSION,
    PIRATE_A_SHIP,
    { ROCKET },
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    THIN_SHIP_HEALTH,
    PIRATE_A_COLLIDERS,
    PIRATE_EXPLOSION_SOUND
};

const ShipParams PIRATE_B_PARAMS =
{
    PIRATE_B,
    PIRATE_B_SHIP,
    PIRATE_B_SHIP_EXPLOSION,
    PIRATE_B_SHIP,
    { ROCKET },
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    THIN_SHIP_HEALTH,
    PIRATE_B_COLLIDERS,
    PIRATE_EXPLOSION_SOUND
};

const ShipParams PIRATE_C_PARAMS =
{
    PIRATE_C,
    PIRATE_C_SHIP,
    PIRATE_C_SHIP_EXPLOSION,
    PIRATE_C_SHIP,
    { ROCKET },
    SHIP_SPEED_SUPERFAST,
    THIN_SHIP_ARMOR,
    THIN_SHIP_HEALTH,
    PIRATE_C_COLLIDERS,
    PIRATE_EXPLOSION_SOUND
};

const ShipParams PIRATE_D_PARAMS =
{
    PIRATE_D,
    PIRATE_D_SHIP,
    PIRATE_D_SHIP_EXPLOSION,
    PIRATE_D_SHIP,
    { ROCKET },
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    THIN_SHIP_HEALTH,
    PIRATE_D_COLLIDERS,
    PIRATE_EXPLOSION_SOUND
};

const ShipParams PIRATE_E_PARAMS =
{
    PIRATE_E,
    PIRATE_E_SHIP,
    PIRATE_E_SHIP_EXPLOSION,
    PIRATE_E_SHIP,
    { ROCKET_DOUBLE },
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    AVERAGE_SHIP_HEALTH,
    PIRATE_E_COLLIDERS,
    PIRATE_EXPLOSION_SOUND,
    {
        { ROCKET_DOUBLE, PIRATE_E_DOUBLE_GUN_POS }
    }
};

const ShipParams PIRATE_F_PARAMS =
{
    PIRATE_F,
    PIRATE_F_SHIP,
    PIRATE_F_SHIP_EXPLOSION,
    PIRATE_F_SHIP,
    { ROCKET },
    SHIP_SPEED_FAST,
    THIN_SHIP_ARMOR,
    AVERAGE_SHIP_HEALTH,
    PIRATE_F_COLLIDERS,
    PIRATE_EXPLOSION_SOUND
};

const ShipParams BOSS_A_PARAMS =
{
    BOSS_A,
    BOSS_A_SHIP,
    BOSS_A_SHIP_EXPLOSION,
    BOSS_A_SHIP,
    { ROCKET, ROCKET_DIFFUSER, ROCKET_DOUBLE },
    SHIP_SPEED_AVERAGE,
    STRONG_SHIP_ARMOR,
    STRONG_SHIP_HEALTH,
    BOSS_A_COLLIDERS,
    BOSS_DEFEATED_SOUND,
    {
        { ROCKET_DIFFUSER, BOSS_DIFFUSER_GUN_POS },
        { ROCKET_DOUBLE, BOSS_DOUBLE_GUN_POS }
    }
};