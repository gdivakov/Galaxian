#include <iostream>
#include <vector>
#include "Ship.h"

Colliders& addVector(Colliders& colliders, Vector2& v);
void rotateColliders(Colliders& colliders, int angle);

Ship::Ship(
    const App* p_system,
    ShipParams params,
    LevelBase* p_level,
    Ship* p_collidedShip
) : system(p_system),
    Texture(p_system->getRenderer()),
    level(p_level),
    colliders(params.colliders)
{
    frame = 0;
    rotation = 0;
    vel = Vector2();
    maxSpeed = params.maxSpeed;
    collidedShip = p_collidedShip;

    gun = new WeaponModule(params.gunType, p_system, this);

    loadFromSprite(params.sprite.path, params.sprite);

    size = { getWidth(), getHeight() };
    wrapperCollider.r = size.h > size.w ? size.h/2 : size.w/2;

    shiftColliders();
}

bool Ship::checkWrapperCollision()
{
    int distanceSquared = Vector2::getDistanceSquared(collidedShip->wrapperCollider.pos, wrapperCollider.pos);
    int radiusesSquared = pow(wrapperCollider.r + collidedShip->wrapperCollider.r, 2);

    if (distanceSquared > radiusesSquared)
    {
        return false;
    }

    return true;
}

bool Ship::checkCollision()
{
    if (collidedShip == NULL)
    {
        return false;
    }

    //Colliders preparedColliders = getColliders(WORLD, enemy);
}

void Ship::move()
{
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

    if (collidedShip != NULL && checkWrapperCollision())
    {
        checkCollision();
    }
}

void Ship::shiftColliders()
{
    wrapperCollider.pos = pos;
}

void Ship::showColliders()
{
    // Display wrapper collider
    DrawCircle(renderer, wrapperCollider.pos.x, wrapperCollider.pos.y, wrapperCollider.r);

    // Display inner colliders
    Colliders preparedColliders = getColliders(WORLD);

    for (int i = 0; i < preparedColliders.size(); i++)
    {
        SDL_RenderDrawLine(renderer, preparedColliders[i].a.x, preparedColliders[i].a.y, preparedColliders[i].b.x, preparedColliders[i].b.y);
        SDL_RenderDrawLine(renderer, preparedColliders[i].b.x, preparedColliders[i].b.y, preparedColliders[i].c.x, preparedColliders[i].c.y);
        SDL_RenderDrawLine(renderer, preparedColliders[i].c.x, preparedColliders[i].c.y, preparedColliders[i].d.x, preparedColliders[i].d.y);
        SDL_RenderDrawLine(renderer, preparedColliders[i].d.x, preparedColliders[i].d.y, preparedColliders[i].a.x, preparedColliders[i].a.y);
    }
}

Colliders Ship::getColliders(Space space, Ship* enemy)
{
    Colliders preparedColliders = colliders;
    rotateColliders(preparedColliders, rotation);

    if (enemy == NULL)
    {
        return space == LOCAL ? colliders : addVector(preparedColliders, pos);
    }

    if (enemy) // Return position relative to the enemy ship
    {
        Vector2 parentToShip = pos - enemy->pos;
        Vector2 parentToShipRotated = Vector2::getRotatedVector(parentToShip, enemy->rotation);
        rotateColliders(preparedColliders, enemy->rotation);
        addVector(preparedColliders, parentToShipRotated);

        return space == LOCAL ? preparedColliders : addVector(preparedColliders, enemy->pos);
    }
}

void Ship::onAfterRender()
{
    gun->onAfterRender();
    
    int clipLength = getClips().size();

    ++frame;
    if (frame / clipLength >= clipLength)
    {
    	frame = 0;
    }
}

Ship::~Ship()
{
    delete gun;
    gun = NULL;
    system = NULL;
    level = NULL;
}

void rotateColliders(Colliders& colliders, int angle)
{
    for (int i = 0; i < colliders.size(); i++)
    {
        colliders[i].a = Vector2::getRotatedVector(colliders[i].a, angle);
        colliders[i].b = Vector2::getRotatedVector(colliders[i].b, angle);
        colliders[i].c = Vector2::getRotatedVector(colliders[i].c, angle);
        colliders[i].d = Vector2::getRotatedVector(colliders[i].d, angle);
    }
}

Colliders& addVector(Colliders& colliders, Vector2& v)
{
    for (int i = 0; i < colliders.size(); i++)
    {
        colliders[i].a += v;
        colliders[i].b += v;
        colliders[i].c += v;
        colliders[i].d += v;
    }

    return colliders;
}