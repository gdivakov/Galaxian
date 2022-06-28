#pragma once
#include "ShipConsts.h"
#include "SoundConst.h"

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
    GAME_OVER_SOUND                             // explosionSound 
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
    GAME_OVER_SOUND
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
    GAME_OVER_SOUND
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
    PIRATE_A_COLLIDERS,
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
    BOSS_DEFEATED
};