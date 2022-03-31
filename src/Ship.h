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
    Ship(const App* system, std::string path, ShipParams params, LevelBase* p_level); //Todo: remove renderer passing?
    ~Ship();

    void move();
    ShipRect getRect() { return { pos, size }; };

    //bool checkCollision(Circle& a, Circle& b);
    //bool checkCollision(Circle& a, SDL_Rect& b);

    virtual void onBeforeRender() = 0;
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e) {};
private:
    Circle collider;
    const App* system;
    Ship* collidedShip;

    //void shiftColliders();
    //Circle& getCollider();
    //bool checkCollision(Ship* p_collidedShip);
protected:
    int maxSpeed;
    int frame;

    Vector2 pos;
    Vector2 vel;
    WeaponModule* gun;
};