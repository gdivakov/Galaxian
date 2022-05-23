#include <iostream>
#include <vector>
#include <algorithm>

#include "Ship.h"
#include "SoundConst.h"
#include "BuffModule.h"

class BuffModule;

Extrems getExtrems(std::vector<float> values);

Ship::Ship(const App* p_system, ShipParams params, LevelBase* p_level, bool isEnemyShip)
    :
    Texture(p_system->getRenderer()),
    Collidable(
        p_system->getRenderer(),
        COLLIDABLE_SHIP,
        params.sprite.imageH > params.sprite.imageW
        ? params.sprite.imageH / 2
        : params.sprite.imageW / 2,
        params.colliders
    ),
    level(p_level)
{
    resetAnimation();
    rotation = 0;
    vel = Vector2();
    maxSpeed = params.maxSpeed;
    explosion = params.explosion;
    explosionSound = params.explosionSound;
    isPlayer = !isEnemyShip;
    isAccelerated = false;
    type = params.type;

    gun = new WeaponModule(params.guns, p_system, this, isEnemyShip);
    specials.status = new StatusModule(params.health, params.armor);
    specials.buff = new BuffModule(this);

    loadFromSprite(params.sprite);
    
    Vector2 top(pos.x, pos.y);
    Vector2 center = pos + Vector2(0, size.h / 2);

    dir = top - center;

    shiftColliders();

    animatedBuff = new AnimatedBuffManager(this);
}

void Ship::move()
{
    if (!isActive)
    {
        return;
    }

    Vector2 prevPos = pos;
    pos += vel;
    shiftColliders();

    // Check boundaries
    if ((pos.x - size.w/2 < 0) || (pos.x + size.w / 2 > level->getSystem()->getWindowSize()->w))
    {
        pos.x -= vel.x;
        shiftColliders();
    }

    if ((pos.y - size.h/2 < 0) || (pos.y + size.h / 2 > level->getSystem()->getWindowSize()->h))
    {
        pos.y -= vel.y;
        shiftColliders();
    }

    checkCollision();
}

void Ship::shiftColliders()
{
    wrapperCollider.pos = pos;
    Collidable::rotation = rotation;
}

void Ship::handleCollided()
{
    if (!isActive)
    {
        return;
    }
    
    switch (collidedTo->type) {
        case COLLIDABLE_SHIP:
            if (specials.buff->hasBuff(BUFF_SUPERPOWER) || 
                specials.buff->hasBuff(BUFF_BREAK_HAND))
            {
                break;
            }

            specials.status->kill(); break;
        case COLLIDABLE_BUFF:
            break;
        default:
            if ( 
                specials.buff->hasBuff(BUFF_SUPERPOWER) ||
                specials.buff->hasBuff(BUFF_SHIELD)
            )
            {
                break; // Prevent from damage
            }

            specials.status->handleHit(collidedTo);
    }


    if (specials.status->getHealth() <= 0)
    {
        if (specials.buff->hasBuff(BUFF_SAVE_HAND))
        {
            specials.status->refreshHealth();
            specials.buff->removeBuff(BUFF_SAVE_HAND);
        }
        else {
            destroyCollidable();
        }
    }
}

void Ship::destroyCollidable()
{
    isActive = false;

    loadFromSprite(explosion);
    resetAnimation();
    level->getSystem()->getAudioPlayer()->playSound(explosionSound);

    unlinkFrom();
}

void Ship::onAfterRender()
{
    int clipLength = getClips().size();

    gun->onAfterRender();
    specials.buff->updateBuffs();
    
    ++frame;

    if (specials.status->getHealth() <= 0 && frame / clipLength >= clipLength)
    {
        level->getSpawner()->removeObject(this);
        return;
    }

    if (frame / clipLength >= clipLength)
    {
        resetAnimation();
    }

    accelerate();
}

void Ship::rotate(int r)
{
    rotation = r;

    if (rotation > 360.0f)
    {
        rotation -= 360.0f;
    }

    if (rotation < 0.0f)
    {
        rotation += 360.0f;
    }

    shiftColliders();
}

Vector2 Ship::getDirection(Space space, bool isRotated)
{
    if (!isRotated)
    {
        return space == LOCAL ? dir : dir + pos;
    }

    Vector2 preparedDir = Vector2::getRotatedVector(dir, rotation);

    return space == LOCAL ? preparedDir : preparedDir + pos;
}

void Ship::refreshHealth() 
{ 
    specials.status->refreshHealth();
};

void Ship::refreshArmor()
{
    specials.status->refreshArmor();
}

Ship::~Ship()
{
    delete gun;
    delete specials.buff;
    delete specials.status;

    gun = NULL;
    level = NULL;
    specials.buff = NULL;
    specials.status = NULL;

    delete animatedBuff;
    animatedBuff = NULL;
}