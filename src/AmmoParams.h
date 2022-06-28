#pragma once
#include "AmmoConsts.h"

const GunParams BLAST_GUN_PARAMS = { BLAST_COOLDOWN, BLAST_SOUND };
const GunParams ROCKET_GUN_PARAMS = { ROCKET_COOLDOWN, ROCKET_SOUND };

const AmmoParams BLAST_PJ_PARAMS =
{
    BLAST_AMMO_SPEED,
    BLAST_AMMO_TEXTURE_PARAMS,
    BLAST_AMMO_LAUNCH_TEXTURE_PARAMS,
    BLAST_AMMO_EXPLOSION_TEXTURE_PARAMS,
    BLAST_AMMO_COLLIDER,
    COLLIDABLE_PROJECTILE_BLAST,
};

const AmmoParams BLAST_DIFFUSER_PJ_PARAMS =
{
    BLAST_AMMO_SPEED,
    BLAST_AMMO_TEXTURE_PARAMS,
    BLAST_AMMO_TEXTURE_PARAMS,
    BLAST_AMMO_EXPLOSION_TEXTURE_PARAMS,
    BLAST_AMMO_COLLIDER,
    COLLIDABLE_PROJECTILE_BLAST
};

const AmmoParams ROCKET_PJ_PARAMS =
{
    ROCKET_AMMO_SPEED,
    ROCKET_AMMO_TEXTURE_PARAMS,
    ROCKET_AMMO_LAUNCH_TEXTURE_PARAMS,
    ROCKET_AMMO_EXPLOSION_TEXTURE_PARAMS,
    ROCKET_AMMO_COLLIDER,
    COLLIDABLE_PROJECTILE_ROCKET,
};

const AmmoParams ROCKET_DIFFUSER_PJ_PARAMS =
{
    DIFFUSER_AMMO_SPEED,
    ROCKET_AMMO_TEXTURE_PARAMS,
    ROCKET_AMMO_TEXTURE_PARAMS,
    ROCKET_AMMO_EXPLOSION_TEXTURE_PARAMS,
    ROCKET_AMMO_COLLIDER,
    COLLIDABLE_PROJECTILE_ROCKET
};