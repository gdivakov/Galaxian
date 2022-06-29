#include "ShipConsts.h"
#include <time.h>

const std::vector<std::vector<BezierCurve>> PIRATE_PATHS =
{
    {
        { Vector2(100, 10), Vector2(350, 60), Vector2(350, 160), Vector2(300, 260) },
        { Vector2(300, 260), Vector2(600, 700), Vector2(500, 300), Vector2(900, 100) },
        { Vector2(800, 90), Vector2(600, 70), Vector2(500, 50), Vector2(400, 10) }
    },
    {
        { Vector2(800, 10), Vector2(500, 60), Vector2(300, 100), Vector2(100, 150) },
        { Vector2(200, 500), Vector2(400, 600), Vector2(500, 900), Vector2(600, 600) },
    },
    {
        { Vector2(900, 10), Vector2(300, 60), Vector2(200, 260), Vector2(300, 300) },
        { Vector2(300, 300), Vector2(400, 500), Vector2(500, 300), Vector2(600, 500) },
        { Vector2(700, 400), Vector2(750, 300), Vector2(800, 200), Vector2(950, 100) },
    },
    {
        { Vector2(500, 10), Vector2(500, 200), Vector2(800, 400), Vector2(700, 600) },
        { Vector2(700, 500), Vector2(600, 650), Vector2(500, 600), Vector2(200, 400) },
        { Vector2(150, 300), Vector2(100, 250), Vector2(50, 80), Vector2(10, 10) }
    },
    {
        { Vector2(10, 500), Vector2(200, 400), Vector2(300, 200), Vector2(400, 400) },
        { Vector2(700, 500), Vector2(600, 650), Vector2(500, 600), Vector2(200, 400) }
    },
    {
        { Vector2(900, 100), Vector2(600, 350), Vector2(350, 200), Vector2(300, 300) },
        { Vector2(350, 350), Vector2(400, 500), Vector2(400, 540), Vector2(550, 560) },
        { Vector2(600, 550), Vector2(800, 350), Vector2(850, 300), Vector2(950, 360) }
    },
    {
        { Vector2(100, 50), Vector2(130, 100), Vector2(200, 200), Vector2(300, 500) },
        { Vector2(350, 500), Vector2(400, 550), Vector2(550, 600), Vector2(600, 660) },
        { Vector2(650, 500), Vector2(710, 400), Vector2(850, 350), Vector2(900, 300) },
        { Vector2(950, 250), Vector2(710, 200), Vector2(650, 150), Vector2(400, 50) }
    },
    {
        { Vector2(700, 50), Vector2(600, 100), Vector2(500, 200), Vector2(500, 400) },
        { Vector2(550, 450), Vector2(600, 500), Vector2(760, 550), Vector2(900, 600) },
        { Vector2(950, 700), Vector2(950, 500), Vector2(950, 450), Vector2(900, 300) },
    },
};

std::vector<BezierCurve> getEnemyPathCurves()
{
    int index = getRandom(PIRATE_PATHS.size());
    return PIRATE_PATHS.at(index);
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