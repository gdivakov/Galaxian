#pragma once
#include <iostream>
#include <vector>
#include "PlayerShip.h"
#include "Vector2.h"
#include "Ship.h"
#include "BezierPath.h"
#include "LevelBase.h"
#include "Consts.h"
#include "ShipConsts.h"

class EnemyShip : public Ship
{
private:
    bool inView;
    std::vector<Vector2> path;
    int currentWaypoint;
    const float EPSILON = 5.0f;
    PlayerShip* player;
    void isInView();
    void followPath();
    void displayPath();
public:
    EnemyShip(
        const App* p_system, 
        LevelBase* p_level, 
        ShipType type, 
        PlayerShip* playerShip,
        std::vector<BezierCurve> pathCurves
    );
    virtual ~EnemyShip();
    virtual void onBeforeRender();
    //void checkDirections();
    virtual void handleEvent(SDL_Event& e);
};