#include "AmmoConsts.h"

int getRadius(GunType type)
{
    AmmoParams params = AMMO_PARAMS.at(type);
    return params.texture.imageH > params.texture.imageW ? params.texture.imageH / 2 : params.texture.imageW / 2;
}