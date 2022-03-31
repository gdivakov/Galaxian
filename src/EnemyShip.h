#pragma once

#include <iostream>
#include <vector>
#include "PlayerShip.h"
#include "Vector2.h"
#include "Ship.h"
#include "BezierPath.h"
#include "LevelBase.h"

// Todo: replace rect by a vector2
class EnemyShip : public Ship
{
    int rotation;
    Vector2 dir;
    bool inView;
    std::vector<Vector2> path;
    int currentWaypoint;
    const float EPSILON = 5.0f;
    PlayerShip* player;
public:
    EnemyShip(
        const App* p_system, 
        LevelBase* p_level, 
        std::string p_path, 
        ShipParams& params, 
        PlayerShip* p_player,
        std::vector<BezierCurve> pathCurves
    );
    virtual void onBeforeRender();
    //void checkDirections();
    virtual void handleEvent(SDL_Event& e);
    void isInView();
    void rotate(int r);
    void followPath();
    void displayPath();
    void updateDirection(float rotateVal, bool clockwise = true);
};