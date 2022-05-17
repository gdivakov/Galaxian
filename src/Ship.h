#pragma once
#include <SDL.h>

#include "Texture.h"
#include "Consts.h"
#include "ShipConsts.h"
#include "ShipSpecialsConsts.h"
#include "WeaponModule.h"
#include "App.h"
#include "LevelBase.h"
#include "Vector2.h"
#include "Collidable.h"
#include "LevelBase.h"
#include "StatusModule.h"
#include "BuffModule.h"
#include "AnimatedBuffManager.h"

class LevelBase;
class StatusModule;
class BuffModule;
class AnimatedBuffManager;

struct ShipSpecials
{
    StatusModule* status;
    BuffModule* buff;
};

class Ship : public Texture, public Collidable
{
public:
    LevelBase* level;
    Ship(const App* system, ShipParams params, LevelBase* p_level, bool isEnemyShip);
    ~Ship();
    void move();
    ShipRect getRect() { return { pos, size }; };
    ShipType getType() { return type; };
    Vector2 getDirection(Space space = WORLD, bool isRotated = true);
    int getRotation() { return rotation; };
    ShipSpecials* getSpecials() { return &specials; };
    void refreshHealth();
    void refreshArmor();
    void resetAnimation() { frame = 0; };
    bool getIsPlayer() { return isPlayer; };
    bool getIsAccelerated () { return isAccelerated; };
    AnimatedBuffManager* animatedBuff;

    virtual void onBeforeRender() = 0;
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e) {};
    virtual void handleCollided();
    virtual void destroyCollidable();
    virtual void startAccelerate() = 0;
private:
    virtual void shiftColliders();
    std::string explosionSound;
    ShipType type;
protected:
    Vector2 pos;
    Vector2 vel;
    Vector2 dir;
    int maxSpeed;
    int frame;
    int rotation;
    bool isPlayer;
    bool isAccelerated;
    WeaponModule* gun;
    ShipSpecials specials;
    SpriteParams explosion;

    void rotate(int r);
    virtual void accelerate() = 0;
};