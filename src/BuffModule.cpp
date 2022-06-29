#include "BuffModule.h"
#include "Audio.h"
#include "General.h"
#include "PlayerShip.h"

BuffModule::BuffModule(Ship* p_ship) 
{ 
    ship = p_ship;
};

void BuffModule::updateBuffs()
{
    Uint32 currentTime = ship->level->getSystem()->getTimer()->getTicks();

    for (Buffs::iterator i = appliedBuffs.begin(); i != appliedBuffs.end();)
    {
        std::string key = i->first;
        BuffParams params = i->second;
        
        if (params.startTime + params.duration < currentTime)
        {
            // Time expired
            i = appliedBuffs.erase(i++);
        }
        else
        {
            ++i;
        }
    }
}

void BuffModule::addBuff(BuffType nextBuff) { 
    Uint32 currentTime = ship->level->getSystem()->getTimer()->getTicks();
    BuffParams nextParams = getBuffParamsByType(nextBuff, currentTime);
    Audio* audio = ship->level->getSystem()->getAudioPlayer();

    if (nextBuff != BUFF_SPEED_UP)
    {
        audio->playSound(BUFF_APPLIED_SOUND);
    }

    switch (nextBuff)
    {
        case BUFF_HEALTH_UP:
            ship->refreshHealth();
            ship->animatedBuff->loadBuffAnimation(nextBuff);
            break;
        case BUFF_ARMOR_UP:
            ship->refreshArmor();
            ship->animatedBuff->loadBuffAnimation(nextBuff);
            break;
        case BUFF_SPEED_UP:
            if (instanceof<PlayerShip>(ship))
            {
                audio->playSound(BUFF_SPEED_UP_SOUND);

                ship->level->accelerate();
                ship->animatedBuff->loadBuffAnimation(nextBuff);
                appliedBuffs[nextParams.sprite.path] = nextParams;
            }
            break;
        default: 
            // Other buffs
            ship->animatedBuff->loadBuffAnimation(nextBuff);
            appliedBuffs[nextParams.sprite.path] = nextParams;
    }
};

void BuffModule::removeBuff(BuffType buff)
{
    BuffParams params = getBuffParamsByType(buff);

    appliedBuffs.erase(params.sprite.path);
}

bool BuffModule::hasBuff(BuffType buff)
{
    BuffParams params = getBuffParamsByType(buff);

    return appliedBuffs.count(params.sprite.path);
}

BuffModule::~BuffModule() 
{ 
    ship = nullptr;
};