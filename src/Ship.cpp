#include <iostream>
#include <vector>
#include "Ship.h"

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
    gun = new WeaponModule(params.gunType, p_system, this);
    frame = 0;
    vel = Vector2();
    maxSpeed = params.maxSpeed;
    collidedShip = p_collidedShip;

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

    std::vector<SDL_Rect>& a = colliders;
    std::vector<SDL_Rect>& b = collidedShip->colliders;

    int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

    for (int Abox = 0; Abox < a.size(); Abox++)
    {
        leftA = a[Abox].x;
        rightA = a[Abox].x + a[Abox].w;
        topA = a[Abox].y;
        bottomA = a[Abox].y + a[Abox].h;
        
        for (int Bbox = 0; Bbox < b.size(); Bbox++)
        {
            leftB = b[Bbox].x;
            rightB = b[Bbox].x + b[Bbox].w;
            topB = b[Bbox].y;
            bottomB = b[Bbox].y + b[Bbox].h;

            //If no sides from A are outside of B
            if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
            {
                //A collision is detected
                std::cout << "Collided" << std::endl;
                return true;
            }
        }
    }

    return false;
}

void Ship::move()
{
    pos += vel;
    shiftColliders();

    // Check boundaries
    if ((pos.x < 0) || (pos.x + size.w/2 > system->getWindowSize()->w))
    {
        pos.x -= vel.x;
        shiftColliders();
    }

    if ((pos.y < 0) || (pos.y + size.h/2 > system->getWindowSize()->h))
    {
        pos.y -= vel.y;
        shiftColliders();
    }

    if (collidedShip != NULL && checkWrapperCollision())
    {
        shiftColliders();
        checkCollision();
    }
}

void Ship::shiftColliders()
{
    wrapperCollider.pos = pos;

    int offsetHeight = 0;

    for (int i = 0; i < colliders.size(); i++)
    {
        colliders[i].x = pos.x - size.w/2 + (size.w - colliders[i].w) / 2;
        colliders[i].y = pos.y - size.h/2 + offsetHeight;

        offsetHeight += colliders[i].h;
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