#pragma once

#include <iostream>
#include <vector>
#include "PlayerShip.h"
#include "Vector2.h"
#include "Ship.h"
#include "BezierPath.h"

class EnemyShip : public Ship
{
    SDL_Rect* playerRect;
    int rotation;
    Vector2 dir;
    bool inView;
    std::vector<Vector2> path;
    int currentWaypoint;
    const float EPSILON = 5.0f;
public:
    EnemyShip(const App* p_system, std::string p_path, ShipParams& params, PlayerShip& player);
    virtual void onBeforeRender();
    virtual void onAfterRender();
    //void checkDirections();
    virtual void handleEvent(SDL_Event& e);
    void isInView();
    void rotate(int r);
    void followPath();
    void displayPath();
    void updateDirection(float rotateVal, bool clockwise = true);
    ~EnemyShip();
};

// todo: replace rect by a vector2