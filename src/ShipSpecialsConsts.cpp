#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#include "ShipSpecialsConsts.h"

BuffParams getBuffParamsByType(BuffType type, Uint32 startTime)
{
    BuffParams nextBuff;

    switch (type)
    {
    case BUFF_RANDOM:
        srand(time(NULL));
        //nextBuff = *availableBuffParams[rand() % availableBuffParams.size()];
        nextBuff = speedUp;
        break;
    case BUFF_ARMOR_UP:
        nextBuff = armorUp; break;
    case BUFF_BREAK_HAND:
        nextBuff = breakHand; break;
    case BUFF_HEALTH_UP:
        nextBuff = healthUp; break;
    case BUFF_SAVE_HAND:
        nextBuff = saveHand; break;
    case BUFF_SHIELD:
        nextBuff = shield; break;
    case BUFF_SPEED_UP:
        nextBuff = speedUp; break;
    case BUFF_SUPERPOWER:
        nextBuff = superpower; break;
    }
    nextBuff.startTime = startTime;

    return nextBuff;
};