#pragma once
#include "Collidable.h"

class StatusModule
{
private:
    int health;
    int armor;
    const int maxHealth;
    const int maxArmor;
public:
    StatusModule(int p_maxHealth, int p_maxArmor) :
        maxHealth(p_maxHealth),
        health(p_maxHealth),
        maxArmor(p_maxArmor),
        armor(p_maxArmor) {};
    ~StatusModule() {};

    int getHealth() { return health; };
    int getMaxHealth() { return maxHealth; };
    int getMaxArmor() { return maxArmor; };
    int getArmor() { return armor; };
    void kill() { armor = health = 0; };
    void handleHit(Collidable* pj);
    void refreshHealth() { health = maxHealth; };
    void refreshArmor() { armor = maxArmor; };
};

