#pragma once
#include <iostream>
#include <vector>

#include "Vector2.h"
#include "Ship.h"
#include "BezierPath.h"
#include "LevelBase.h"
#include "ShipConsts.h"

class EnemyShip : public Ship
{
private:
    std::vector<Vector2> path;
    const float EPSILON = 5.0f;
public:
    EnemyShip(
        LevelBase* p_level, 
        ShipType type, 
        std::vector<BezierCurve> pathCurves
    );
    void onAccelerate();

    virtual void onBeforeRender();
    virtual void handleEvent(SDL_Event& e);
protected:
    virtual void handleAcceleration();
    bool isInView();
    void addPath(std::vector<BezierCurve> pathCurves);
    void followPath(bool withDirRotation = true);
    void displayPath();
    bool inView;
    bool isFalling;
    int currentWaypoint;
};