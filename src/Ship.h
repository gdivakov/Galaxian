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
    WeaponModule* getGun() { return gun; };
    AnimatedBuffManager* animatedBuff;

    virtual void onBeforeRender() = 0;
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e) {};
    virtual void handleCollided();
    virtual void destroyCollidable();
    virtual void startAcceleration() = 0;
private:
    void updatePosByVelocity();
    std::string explosionSound;
    ShipType type;
protected:
    virtual void shiftColliders();
    Vector2 pos;
    Vector2 vel;
    Vector2 dir;
    int maxSpeed;
    int frame;
    int rotation;
    bool isPlayer;
    WeaponModule* gun;
    ShipSpecials specials;
    SpriteParams explosion;

    void rotate(int r);
    virtual void handleAcceleration() = 0;
    void setMaxSpeed(int nextMaxSpeed) { maxSpeed = nextMaxSpeed; };
};