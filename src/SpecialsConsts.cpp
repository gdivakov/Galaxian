#include <time.h>
#include "SpecialsConsts.h"

int rand_between(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

BuffParams getBuffParamsByType(BuffType type, Uint32 startTime)
{
    BuffParams nextBuff;

    if (type == BUFF_RANDOM)
    {
        srand(time(NULL));

        auto random_it = std::next(BUFF_PARAMS.begin(), rand_between(0, BUFF_PARAMS.size() - 1));
        nextBuff = random_it.operator*().second;
    }
    else
    {
        nextBuff = BUFF_PARAMS.at(type);
    }

    nextBuff.startTime = startTime;

    return nextBuff;
};
