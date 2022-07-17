#include <iostream>
#include <vector>
#include <algorithm>

#include "Ship.h"
#include "SoundConst.h"
#include "BuffModule.h"

class BuffModule;

Extrems getExtrems(std::vector<float> values);

Ship::Ship(const App* p_system, ShipParams params, LevelBase* p_level)
    :
    Collidable(
        p_system->getRenderer(),
        COLLIDABLE_SHIP,
        params.sprite.imageH > params.sprite.imageW
        ? params.sprite.imageH / 2
        : params.sprite.imageW / 2,
        params.colliders)
{
    rotation = 0;
    vel = Vector2();
    level = p_level;
    maxSpeed = params.maxSpeed;
    explosionSound = params.explosionSound;
    type = params.type;
    resetAnimation();
    SDL_Renderer* renderer = p_system->getRenderer();
    textures = 
    { 
        new Texture(renderer, params.sprite),
        new Texture(renderer, params.explosion),
        new Texture(renderer, params.accelerate)
    };

    textures.selected = textures.common;

    gun = new WeaponModule(params.guns, p_system, this);

    specials.status = new StatusModule(params.health, params.armor);
    specials.buff = new BuffModule(this);

    
    Vector2 top(pos.x, pos.y);
    Vector2 center = pos + Vector2(0, textures.selected->size.h / 2);

    dir = top - center;

    shiftColliders();

    animatedBuff = new AnimatedBuffManager(this);
}

Ship::~Ship()
{
    unlink();

    delete gun;
    delete specials.buff;
    delete specials.status;
    delete textures.common;
    delete textures.accelerate;
    delete textures.explosion;
    delete animatedBuff;

    gun = nullptr;
    level = nullptr;
    specials.buff = nullptr;
    specials.status = nullptr;
    textures.common = nullptr;
    textures.accelerate = nullptr;
    textures.explosion = nullptr;
    textures.selected = nullptr;
    animatedBuff = nullptr;
}

void Ship::onAccelerate()
{
    textures.selected = textures.accelerate;
}

void Ship::onAccelerateEnd()
{
    textures.selected = textures.common;
}

void Ship::move()
{
    if (!isActive)
    {
        return;
    }

    updatePosByVelocity();
    checkCollision();
}

void Ship::updatePosByVelocity()
{
    pos += vel;
    shiftColliders();

    // Check boundaries
    if ((pos.x - textures.selected->size.w / 2 < 0) || (pos.x + textures.selected->size.w / 2 > level->getSystem()->getWindowSize()->w))
    {
        pos.x -= vel.x;
        shiftColliders();
    }

    if ((pos.y - textures.selected->size.h / 2 < 0) || (pos.y + textures.selected->size.h / 2 > level->getSystem()->getWindowSize()->h))
    {
        pos.y -= vel.y;
        shiftColliders();
    }
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
    Audio* audioPlayer = level->getSystem()->getAudioPlayer();
    audioPlayer->stopSounds();
    audioPlayer->playSound(explosionSound);

    isActive = false;

    textures.selected = textures.explosion;
    resetAnimation();

    unlink();
}

void Ship::onAfterRender()
{
    int clipLength = textures.selected->getClips().size();

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

    handleAcceleration();
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