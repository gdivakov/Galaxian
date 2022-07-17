#include "CollidersConsts.h"
#include <algorithm>

Extrems getExtrems(std::vector<float> values)
{
    Extrems preparedExtrems =
    {
        *std::min_element(values.begin(), values.end()),
        *std::max_element(values.begin(), values.end())
    };

    return preparedExtrems;
}

Colliders& addVectorToCollider(Colliders& colliders, Vector2& v)
{
    for (int i = 0; i < colliders.size(); i++)
    {
        colliders[i].a += v;
        colliders[i].b += v;
        colliders[i].c += v;
        colliders[i].d += v;
    }

    return colliders;
}

Colliders& rotateColliders(Colliders& colliders, int angle)
{
    for (int i = 0; i < colliders.size(); i++)
    {
        colliders[i].a = Vector2::getRotatedVector(colliders[i].a, angle);
        colliders[i].b = Vector2::getRotatedVector(colliders[i].b, angle);
        colliders[i].c = Vector2::getRotatedVector(colliders[i].c, angle);
        colliders[i].d = Vector2::getRotatedVector(colliders[i].d, angle);
    }

    return colliders;
}

RectColliderPoint getColliderProjectionOnAxis(RectColliderPoint& collider, Vector2 axis)
{
    RectColliderPoint projectedCollider =
    {
        collider.a * axis * axis / (axis.x * axis.x + axis.y * axis.y),
        collider.b * axis * axis / (axis.x * axis.x + axis.y * axis.y),
        collider.c * axis * axis / (axis.x * axis.x + axis.y * axis.y),
        collider.d * axis * axis / (axis.x * axis.x + axis.y * axis.y),
    };

    return projectedCollider;
}

std::vector<float> getPointValuesOnAxis(RectColliderPoint& points, Vector2 axis)
{
    std::vector<float> values;
    values.push_back(points.a * axis);
    values.push_back(points.b * axis);
    values.push_back(points.c * axis);
    values.push_back(points.d * axis);

    return values;
}

// Works for rectangles
bool checkOverlapSAT(RectColliderPoint& coll1, RectColliderPoint& coll2)
{
    // Define axis of the ship colliders
    Vector2 axisA = coll1.a - coll1.d;
    Vector2 axisB = coll1.a - coll1.b;
    Vector2 axisC = coll2.a - coll2.d;
    Vector2 axisD = coll2.a - coll2.b;

    // Project collider points to the axis
    RectColliderPoint projectedCollAxisA = getColliderProjectionOnAxis(coll1, axisA);
    RectColliderPoint projectedCollAxisB = getColliderProjectionOnAxis(coll1, axisB);
    RectColliderPoint projectedCollAxisC = getColliderProjectionOnAxis(coll1, axisC);
    RectColliderPoint projectedCollAxisD = getColliderProjectionOnAxis(coll1, axisD);

    RectColliderPoint projectedEnemyCollAxisA = getColliderProjectionOnAxis(coll2, axisA);
    RectColliderPoint projectedEnemyCollAxisB = getColliderProjectionOnAxis(coll2, axisB);
    RectColliderPoint projectedEnemyCollAxisC = getColliderProjectionOnAxis(coll2, axisC);
    RectColliderPoint projectedEnemyCollAxisD = getColliderProjectionOnAxis(coll2, axisD);

    // Define point value relative to the axis
    std::vector<float> pointValuesAxisA = getPointValuesOnAxis(projectedCollAxisA, axisA);
    std::vector<float> pointValuesAxisB = getPointValuesOnAxis(projectedCollAxisB, axisB);
    std::vector<float> pointValuesAxisC = getPointValuesOnAxis(projectedCollAxisC, axisC);
    std::vector<float> pointValuesAxisD = getPointValuesOnAxis(projectedCollAxisD, axisD);

    std::vector<float> pointValuesEnemyAxisA = getPointValuesOnAxis(projectedEnemyCollAxisA, axisA);
    std::vector<float> pointValuesEnemyAxisB = getPointValuesOnAxis(projectedEnemyCollAxisB, axisB);
    std::vector<float> pointValuesEnemyAxisC = getPointValuesOnAxis(projectedEnemyCollAxisC, axisC);
    std::vector<float> pointValuesEnemyAxisD = getPointValuesOnAxis(projectedEnemyCollAxisD, axisD);

    // Define max and min points
    Extrems extremsAxisA = getExtrems(pointValuesAxisA);
    Extrems extremsAxisB = getExtrems(pointValuesAxisB);
    Extrems extremsAxisC = getExtrems(pointValuesAxisC);
    Extrems extremsAxisD = getExtrems(pointValuesAxisD);

    Extrems extremsEnemyAxisA = getExtrems(pointValuesEnemyAxisA);
    Extrems extremsEnemyAxisB = getExtrems(pointValuesEnemyAxisB);
    Extrems extremsEnemyAxisC = getExtrems(pointValuesEnemyAxisC);
    Extrems extremsEnemyAxisD = getExtrems(pointValuesEnemyAxisD);

    short overlap = 0;

    if (extremsAxisA.min <= extremsEnemyAxisA.max && extremsAxisA.max >= extremsEnemyAxisA.min)
    {
        overlap++;
    }

    if (extremsAxisB.min <= extremsEnemyAxisB.max && extremsAxisB.max >= extremsEnemyAxisB.min)
    {
        overlap++;
    }

    if (extremsAxisC.min <= extremsEnemyAxisC.max && extremsAxisC.max >= extremsEnemyAxisC.min)
    {
        overlap++;
    }

    if (extremsAxisD.min <= extremsEnemyAxisD.max && extremsAxisD.max >= extremsEnemyAxisD.min)
    {
        overlap++;
    }

    return overlap == SAT_AXES_TO_CHECK;
}

void renderCollider(SDL_Renderer* renderer, RectColliderPoint& coll)
{
    SDL_RenderDrawLine(renderer, coll.a.x, coll.a.y, coll.b.x, coll.b.y);
    SDL_RenderDrawLine(renderer, coll.b.x, coll.b.y, coll.c.x, coll.c.y);
    SDL_RenderDrawLine(renderer, coll.c.x, coll.c.y, coll.d.x, coll.d.y);
    SDL_RenderDrawLine(renderer, coll.d.x, coll.d.y, coll.a.x, coll.a.y);
}