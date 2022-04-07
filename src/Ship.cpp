#include <iostream>
#include <vector>
#include <algorithm>

#include "Ship.h"

Colliders& addVector(Colliders& colliders, Vector2& v);
Colliders& rotateColliders(Colliders& colliders, int angle);
RectColliderPoint getColliderProjectionOnAxis(RectColliderPoint& collider, Vector2 axis);
std::vector<float> getPointValuesOnAxis(RectColliderPoint& points, Vector2 axis);
float findMaxNumber(std::vector<float> nums);
float findMinNumber(std::vector<float> nums);
Extrems getExtrems(std::vector<float> values);

Ship::Ship(
    const App* p_system,
    ShipParams params,
    LevelBase* p_level,
    Ship* p_collidedShip
) : system(p_system),
    Texture(p_system->getRenderer()),
    level(p_level),
    colliders(params.colliders)
{
    frame = 0;
    rotation = 0;
    vel = Vector2();
    maxSpeed = params.maxSpeed;
    collidedShip = p_collidedShip;

    gun = new WeaponModule(params.gunType, p_system, this);

    loadFromSprite(params.sprite.path, params.sprite);

    size = { getWidth(), getHeight() };
    wrapperCollider.r = size.h > size.w ? size.h/2 : size.w/2;

    shiftColliders();
}

bool Ship::checkWrapperCollision()
{
    int distanceSquared = Vector2::getDistanceSquared(collidedShip->wrapperCollider.pos, wrapperCollider.pos);
    int radiusesSquared = pow(wrapperCollider.r + collidedShip->wrapperCollider.r, 2);

    if (distanceSquared > radiusesSquared)
    {
        return false;
    }

    return true;
}

bool Ship::checkCollision()
{
    if (collidedShip == NULL)
    {
        return false;
    }

    Colliders preparedColliders = colliders;
    Colliders enemyColliders = collidedShip->colliders;
    //Vector2 shift(WINDOWED_WIDTH / 4, WINDOWED_HEIGHT / 4);
    //Vector2 nextPos = collidedShip->pos - shift;
    Vector2 nextPos = Vector2();

    int enemyRotation = collidedShip->rotation;
    int enemyNextRotation = 0;

    enemyNextColliders = rotateColliders(enemyColliders, collidedShip->rotation);
    //enemyNextColliders = addVector(enemyColliders, nextPos);

    Vector2 enemyToShip = pos - collidedShip->pos;
    //Vector2 enemyToShipRotated = Vector2::getRotatedVector(enemyToShip, enemyNextRotation - enemyRotation);

    rotateColliders(preparedColliders, rotation);
    
    nextColliders = addVector(preparedColliders, enemyToShip);
    
    // SAT alghoritm 
    for (int i = 0; i < enemyNextColliders.size(); i++)
    {
        for (int k = 0; k < nextColliders.size(); k++)
        {
            int overlap = 0;
            // Define axis of the ship colliders
            RectColliderPoint& coll = nextColliders[k];
            RectColliderPoint& collEn = enemyNextColliders[i];

            // Define axis
            Vector2 axisA = coll.a - coll.d;
            Vector2 axisB = coll.a - coll.b;
            Vector2 axisC = collEn.a - collEn.d;
            Vector2 axisD = collEn.a - collEn.b;

            // Project collider points to the axis
            RectColliderPoint projectedCollAxisA = getColliderProjectionOnAxis(coll, axisA);
            RectColliderPoint projectedCollAxisB = getColliderProjectionOnAxis(coll, axisB);
            RectColliderPoint projectedCollAxisC = getColliderProjectionOnAxis(coll, axisC);
            RectColliderPoint projectedCollAxisD = getColliderProjectionOnAxis(coll, axisD);

            RectColliderPoint projectedEnemyCollAxisA = getColliderProjectionOnAxis(collEn, axisA);
            RectColliderPoint projectedEnemyCollAxisB = getColliderProjectionOnAxis(collEn, axisB);
            RectColliderPoint projectedEnemyCollAxisC = getColliderProjectionOnAxis(collEn, axisC);
            RectColliderPoint projectedEnemyCollAxisD = getColliderProjectionOnAxis(collEn, axisD);

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

            if (extremsEnemyAxisA.min <= extremsAxisA.max && extremsEnemyAxisA.max >= extremsAxisA.min)
            {
                overlap++;
            }

            if (extremsEnemyAxisB.min <= extremsAxisB.max && extremsEnemyAxisB.max >= extremsAxisB.min)
            {
                overlap++;
            }

            if (extremsEnemyAxisC.min <= extremsAxisC.max && extremsEnemyAxisC.max >= extremsAxisC.min)
            {
                overlap++;
            }

            if (extremsEnemyAxisD.min <= extremsAxisD.max && extremsEnemyAxisD.max >= extremsAxisD.min)
            {
                overlap++;
            }

            if (overlap == 4)
            {
                std::cout << i << " " << k << std::endl;
                return true;
            }
        }
    }
    return false;
}

void Ship::move()
{
    Vector2 prevPos = pos;
    pos += vel;
    shiftColliders();

    // Check boundaries
    if ((pos.x - size.w/2 < 0) || (pos.x + size.w / 2 > system->getWindowSize()->w))
    {
        pos.x -= vel.x;
        shiftColliders();
    }

    if ((pos.y - size.h/2 < 0) || (pos.y + size.h / 2 > system->getWindowSize()->h))
    {
        pos.y -= vel.y;
        shiftColliders();
    }

    if (collidedShip != NULL && checkWrapperCollision())
    {
        bool isCollided = checkCollision();
        if (isCollided)
        {
            //std::cout << "collided" << std::endl << std::endl;
            pos = prevPos;
            shiftColliders();
        }
    }
}

void Ship::shiftColliders()
{
    wrapperCollider.pos = pos;
}

void Ship::showColliders()
{
    // Display wrapper collider
    DrawCircle(renderer, wrapperCollider.pos.x, wrapperCollider.pos.y, wrapperCollider.r);

    // Display inner colliders
    Colliders preparedColliders = getColliders(WORLD, collidedShip);

    for (int i = 0; i < preparedColliders.size(); i++)
    {
        SDL_RenderDrawLine(renderer, preparedColliders[i].a.x, preparedColliders[i].a.y, preparedColliders[i].b.x, preparedColliders[i].b.y);
        SDL_RenderDrawLine(renderer, preparedColliders[i].b.x, preparedColliders[i].b.y, preparedColliders[i].c.x, preparedColliders[i].c.y);
        SDL_RenderDrawLine(renderer, preparedColliders[i].c.x, preparedColliders[i].c.y, preparedColliders[i].d.x, preparedColliders[i].d.y);
        SDL_RenderDrawLine(renderer, preparedColliders[i].d.x, preparedColliders[i].d.y, preparedColliders[i].a.x, preparedColliders[i].a.y);
    }

    if (collidedShip)
    {
        for (int i = 0; i < nextColliders.size(); i++)
        {
            SDL_RenderDrawLine(renderer, nextColliders[i].a.x, nextColliders[i].a.y, nextColliders[i].b.x, nextColliders[i].b.y);
            SDL_RenderDrawLine(renderer, nextColliders[i].b.x, nextColliders[i].b.y, nextColliders[i].c.x, nextColliders[i].c.y);
            SDL_RenderDrawLine(renderer, nextColliders[i].c.x, nextColliders[i].c.y, nextColliders[i].d.x, nextColliders[i].d.y);
            SDL_RenderDrawLine(renderer, nextColliders[i].d.x, nextColliders[i].d.y, nextColliders[i].a.x, nextColliders[i].a.y);
        }

        for (int i = 0; i < enemyNextColliders.size(); i++)
        {
            SDL_RenderDrawLine(renderer, enemyNextColliders[i].a.x, enemyNextColliders[i].a.y, enemyNextColliders[i].b.x, enemyNextColliders[i].b.y);
            SDL_RenderDrawLine(renderer, enemyNextColliders[i].b.x, enemyNextColliders[i].b.y, enemyNextColliders[i].c.x, enemyNextColliders[i].c.y);
            SDL_RenderDrawLine(renderer, enemyNextColliders[i].c.x, enemyNextColliders[i].c.y, enemyNextColliders[i].d.x, enemyNextColliders[i].d.y);
            SDL_RenderDrawLine(renderer, enemyNextColliders[i].d.x, enemyNextColliders[i].d.y, enemyNextColliders[i].a.x, enemyNextColliders[i].a.y);
        }
    }
}

Colliders Ship::getColliders(Space space, Ship* enemy)
{
    Colliders preparedColliders = colliders;
    rotateColliders(preparedColliders, rotation);

    if (enemy == NULL)
    {
        return space == LOCAL ? colliders : addVector(preparedColliders, pos);
    }

    if (enemy) // Return position relative to the enemy ship
    {
        Vector2 parentToShip = pos - enemy->pos;
        //Vector2 parentToShipRotated = Vector2::getRotatedVector(parentToShip, enemy->rotation);
        //rotateColliders(preparedColliders, enemy->rotation);
        addVector(preparedColliders, parentToShip);

        return space == LOCAL ? preparedColliders : addVector(preparedColliders, enemy->pos);
    }
}

void Ship::onAfterRender()
{
    gun->onAfterRender();
    
    int clipLength = getClips().size();

    ++frame;
    if (frame / clipLength >= clipLength)
    {
    	frame = 0;
    }
}

Ship::~Ship()
{
    delete gun;
    gun = NULL;
    system = NULL;
    level = NULL;
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

Colliders& addVector(Colliders& colliders, Vector2& v)
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

RectColliderPoint getColliderProjectionOnAxis(RectColliderPoint& collider, Vector2 axis)
{    
    RectColliderPoint projectedCollider =
    {
        (collider.a * axis / (collider.a.x * collider.a.x + collider.a.y * collider.a.y)) * axis,
        (collider.b * axis / (collider.b.x * collider.b.x + collider.b.y * collider.b.y)) * axis,
        (collider.c * axis / (collider.c.x * collider.c.x + collider.c.y * collider.c.y)) * axis,
        (collider.d * axis / (collider.d.x * collider.d.x + collider.d.y * collider.d.y)) * axis,
    };

    return projectedCollider;
}

std::vector<float> getPointValuesOnAxis(RectColliderPoint& points, Vector2 axis)
{

    std::vector<float> values = {
            points.a * axis,
            points.b * axis,
            points.c * axis,
            points.d * axis
    };

    return values;
}

float findMaxNumber(std::vector<float> nums)
{
    float pNums[] = {nums[0], nums[1], nums[2], nums[3]};
    //return *std::max_element(pNums, pNums + length);
    float max = nums[0];

    for (int i = 1; i < 4; i++)
    {
        if (nums[i] > nums[i - 1])
        {
            max = nums[i];
        }
    }

    return max;
}

float findMinNumber(std::vector<float> nums)
{
    float pNums[] = { nums[0], nums[1], nums[2], nums[3] };
    /*return *std::min_element(pNums, pNums + length);*/
    float min = nums[0];

    for (int i = 1; i < 4; i++)
    {
        if (nums[i] < nums[i - 1])
        {
            min = nums[i];
        }
    }

    return min;
}

Extrems getExtrems(std::vector<float> values)
{
    Extrems preparedExtrems =
    {
        findMinNumber(values),
        findMaxNumber(values)
    };

    return preparedExtrems;
}