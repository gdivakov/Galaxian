#include <time.h>
#include "SpecialsConsts.h"

BuffParams getBuffParamsByType(BuffType type, Uint32 startTime)
{
    BuffParams nextBuff;

    if (type == BUFF_RANDOM)
    {
        auto random_it = std::next(BUFF_PARAMS.begin(), getRandom(BUFF_PARAMS.size()));
        nextBuff = random_it.operator*().second;
    }
    else
    {
        nextBuff = BUFF_PARAMS.at(type);
    }

    nextBuff.startTime = startTime;

    return nextBuff;
};
