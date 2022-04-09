#include <iostream>
#include <vector>
#include <algorithm>

#include "Ship.h"
#include "SoundConst.h"

Extrems getExtrems(std::vector<float> values);

Ship::Ship(const App* p_system, ShipParams params, LevelBase* p_level, bool isEnemyShip) 
:   system(p_system),
    Texture(p_system->getRenderer()),
    Collidable(p_system->getRenderer(), params.colliders, params.sprite.imageH > params.sprite.imageW ? params.sprite.imageH / 2 : params.sprite.imageW / 2),
    level(p_level)
{
    frame = 0;
    rotation = 0;
    vel = Vector2();
    maxSpeed = params.maxSpeed;
    explosion = params.explosion;
    explosionSound = params.explosionSound;

    gun = new WeaponModule(params.gunType, p_system, this, isEnemyShip);

    loadFromSprite(params.sprite);
    
    Vector2 top(pos.x, pos.y);
    Vector2 center = pos + Vector2(0, size.h / 2);

    dir = top - center;

    shiftColliders();
}

void Ship::move()
{
    if (isCollided)
    {
        return;
    }

    Vector2 prevPos = pos;
    pos += vel;
    shiftColliders();

    // Check boundaries
    if ((pos.x - size.w/2 < 0) || (pos.x + size.w / 2 > system->getWindowSize()->w))
    {
        pos.x -= vel.x;
        shiftColliders();
    }

    if ((pos.y - size.h/2 < 0) || (pos.y + size.h / 2 > system->getWindowSize()->h))
    {
        pos.y -= vel.y;
        shiftColliders();
    }

    checkCollision();
}

void Ship::shiftColliders()
{
    wrapperCollider.pos = pos;
    collidableRotation = rotation;
}

void Ship::handleCollided()
{
    loadFromSprite(explosion);
    system->getAudioPlayer()->playSound(explosionSound);

    frame = 0;
}

void Ship::onAfterRender()
{
    gun->onAfterRender();
    
    int clipLength = getClips().size();

    ++frame;

    if (isCollided && frame / clipLength >= clipLength)
    {
        // Remove ship
        level->removeObject(this);
    }

    if (frame / clipLength >= clipLength)
    {
    	frame = 0;
    }
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

Ship::~Ship()
{
    delete gun;
    gun = NULL;
    system = NULL;
    level = NULL;
}