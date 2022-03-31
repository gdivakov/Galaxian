#include <iostream>
#include <vector>
#include "Ship.h"

Ship::Ship(
    const App* p_system,
    std::string path,
    ShipParams params,
    LevelBase* p_level
) : system(p_system),
    Texture(p_system->getRenderer()),
    //type(params.type),
    level(p_level)
{
    gun = new WeaponModule(params.gunType, p_system, this);
    frame = 0;
    vel = Vector2();
    maxSpeed = params.maxSpeed;

    loadFromSprite(path, params.sprite);

    size = { getWidth(), getHeight() };
    collider.r = getHeight()/2; // Todo: change here

    //shiftColliders();
}

//bool checkCollision(Ship* p_collidedShip)
//{
//    
//}

//SDL_Rect* Ship::getRect()
//{
//    return &rect;
//}

void Ship::move()
{
    pos += vel;

    // Check boundaries
    if ((pos.x < 0) || (pos.x + size.w > system->getWindowSize()->w))
    {
        pos.x -= vel.x;
    }

    if ((pos.y < 0) || (pos.y + size.h > system->getWindowSize()->h))
    {
        pos.y -= vel.y;
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