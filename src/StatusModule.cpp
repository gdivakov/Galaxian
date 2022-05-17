#include "StatusModule.h"
#include "ShipConsts.h"

void StatusModule::handleHit(Collidable* pj)
{
    CollidableType type = pj->type;
    int potentialDamage = 0;

    if (type == COLLIDABLE_PROJECTILE_BLAST)
    {
        potentialDamage = BLAST_DAMAGE;
    }

    if (type == COLLIDABLE_PROJECTILE_ROCKET)
    {
        potentialDamage = ROCKET_DAMAGE;
    }

    armor -= potentialDamage;

    health -= armor < 0 ? abs(armor) : 0;
    armor = armor < 0 ? 0 : armor;
}