#pragma once
#include <SDL.h>
#include "Object.h"
#include "Texture.h"
#include "Consts.h"
#include "WeaponModule.h"
#include "App.h"
#include "LevelBase.h"
#include "Vector2.h"

struct ShipRect {
    Vector2 pos;
    Size size;
};

class Ship: public Texture
{
public:
    LevelBase* level;
    Ship(
        const App* system, 
        ShipParams params, 
        LevelBase* p_level,
        Ship* p_collidedShip = NULL
    ); //Todo: remove renderer passing?
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
    int maxSpeed;
    int frame;
    std::vector<SDL_Rect>& colliders;
    Circle wrapperCollider;
    Ship* collidedShip;

    Vector2 pos;
    Vector2 vel;
    WeaponModule* gun;
};