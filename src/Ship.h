#pragma once
#include <SDL.h>

#include "Object.h"
#include "Texture.h"
#include "Consts.h"
#include "ShipConsts.h"
#include "WeaponModule.h"
#include "App.h"
#include "LevelBase.h"
#include "Vector2.h"
#include "Collidable.h"

class Ship : public Texture, public Collidable
{
public:
    LevelBase* level;
    Ship(const App* system, ShipParams params, LevelBase* p_level, bool isEnemyShip);
    ~Ship();
    void move();
    ShipRect getRect() { return { pos, size }; };
    Vector2 getDirection(Space space = WORLD, bool isRotated = true);
    int getRotation() { return rotation; };

    virtual void onBeforeRender() = 0;
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e) {};
    virtual void handleCollided();
private:
    const App* system;
    virtual void shiftColliders();
protected:
    Vector2 pos;
    Vector2 vel;
    Vector2 dir;
    int maxSpeed;
    int frame;
    int rotation;
    WeaponModule* gun;
    SpriteParams explosion;
    void rotate(int r);
};