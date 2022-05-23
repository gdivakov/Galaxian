#pragma once
#include <iostream>
#include <vector>

#include "Vector2.h"
#include "Ship.h"
#include "BezierPath.h"
#include "LevelBase.h"
#include "Consts.h"
#include "ShipConsts.h"

class EnemyShip : public Ship
{
private:
    std::vector<Vector2> path;
    const float EPSILON = 5.0f;
    Ship* player;
public:
    EnemyShip(
        LevelBase* p_level, 
        ShipType type, 
        Ship* playerShip,
        std::vector<BezierCurve> pathCurves
    );
    virtual ~EnemyShip();
    virtual void onBeforeRender();
    //void checkDirections();
    virtual void handleEvent(SDL_Event& e);
    virtual void startAccelerate();
protected:
    virtual void accelerate();
    void isInView();
    void addPath(std::vector<BezierCurve> pathCurves);
    void followPath(bool withDirRotation = true);
    void displayPath();
    bool inView;
    bool isFalling;
    int currentWaypoint;
};