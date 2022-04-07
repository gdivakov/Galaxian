#pragma once

#include <iostream>
#include <vector>
#include "PlayerShip.h"
#include "Vector2.h"
#include "Ship.h"
#include "BezierPath.h"
#include "LevelBase.h"
#include "Consts.h"

// Todo: replace rect by a vector2
class EnemyShip : public Ship
{
    Vector2 dir;
    bool inView;
    std::vector<Vector2> path;
    int currentWaypoint;
    const float EPSILON = 5.0f;
    PlayerShip* player;
    void isInView();
    void rotate(int r);
    void followPath();
    void displayPath();
public:
    EnemyShip(
        const App* p_system, 
        LevelBase* p_level, 
        ShipParams& params, 
        //PlayerShip* p_player,
        std::vector<BezierCurve> pathCurves
    );
    virtual void onBeforeRender();
    //void checkDirections();
    virtual void handleEvent(SDL_Event& e);
};