#pragma once
#include <SDL.h>

#include "Object.h"
#include "Texture.h"
#include "Consts.h"
#include "WeaponModule.h"
#include "App.h"
#include "LevelBase.h"
#include "Vector2.h"

class Ship: public Texture
{
public:
    LevelBase* level;
    Ship(const App* system, ShipParams params, LevelBase* p_level, Ship* p_collidedShip = NULL);
    ~Ship();
    void move();
    ShipRect getRect() { return { pos, size }; };
    bool checkCollision();
    virtual void onBeforeRender() = 0;
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e) {};
private:
    const App* system;
    void shiftColliders();
    bool checkWrapperCollision();
protected:
    Vector2 pos;
    Vector2 vel;
    int maxSpeed;
    int frame;
    Colliders colliders;
    Circle wrapperCollider;
    Ship* collidedShip;
    WeaponModule* gun;
    int rotation;
    void showColliders();
    Colliders getColliders(Space space, Ship* parent = NULL);
    Colliders enemyNextColliders;
    Colliders nextColliders;
};