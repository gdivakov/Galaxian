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

struct ShipTextures
{
    Texture* common;
    Texture* explosion;
    Texture* accelerate;
    Texture* selected;
};

class Ship : public Collidable, public Object
{
public:
    Ship(const App* system, ShipParams params, LevelBase* p_level, bool isEnemyShip);
    ~Ship();

    LevelBase* level;
    AnimatedBuffManager* animatedBuff;

    void move();
    void refreshHealth();
    void refreshArmor();

    ShipRect getRect() { return { pos, textures.selected->size }; };
    ShipType getType() { return type; };
    Vector2 getDirection(Space space = WORLD, bool isRotated = true);
    int getRotation() { return rotation; };
    ShipSpecials* getSpecials() { return &specials; };
    bool getIsPlayer() { return isPlayer; };
    WeaponModule* getGun() { return gun; };
    void resetAnimation() { frame = 0; };
    void onAccelerate();
    void onAccelerateEnd();

    virtual void onBeforeRender() = 0;
    virtual void onAfterRender();
    virtual void handleEvent(SDL_Event& e) {};
    virtual void handleCollided();
    virtual void destroyCollidable();
private:
    void updatePosByVelocity();
    std::string explosionSound;
    ShipType type;
    ShipTextures textures;
protected:
    virtual void shiftColliders();
    Texture* getTexture() { return textures.selected; };
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
    void setMaxSpeed(int nextMaxSpeed) { maxSpeed = nextMaxSpeed; };
    virtual void handleAcceleration() = 0;
};