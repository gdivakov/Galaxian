#include "ShipConsts.h"

std::vector<BezierCurve> getEnemyPathCurves(int enemyCounter)
{
    std::vector<BezierCurve> curves;

    if (enemyCounter == 0)
    {
        curves.push_back({ Vector2(100, 10), Vector2(350, 60), Vector2(350, 160), Vector2(300, 260) });
        curves.push_back({ Vector2(300, 260), Vector2(600, 700), Vector2(500, 300), Vector2(600, 600) });
    }
    else
    {
        curves.push_back({ Vector2(800, 10), Vector2(550, 60), Vector2(550, 160), Vector2(300, 260) });
        curves.push_back({ Vector2(300, 260), Vector2(300, 500), Vector2(100, 100), Vector2(600, 600) });
    }
    
    return curves;
}

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}