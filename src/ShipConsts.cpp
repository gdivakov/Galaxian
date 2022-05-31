#include "ShipConsts.h"

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

float findMaxNumber(std::vector<float> nums)
{
    float max = nums[0];

    for (int i = 1; i < 4; i++)
    {
        if (nums[i] > max)
        {
            max = nums[i];
        }
    }

    return max;
}

float findMinNumber(std::vector<float> nums)
{
    float min = nums[0];

    for (int i = 1; i < 4; i++)
    {
        if (nums[i] < min)
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

const short SAT_AXES_TO_CHECK = 4;

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

GunParams getGunParamsByType(GunType type)
{
    switch (type)
    {
    case BLAST:
        return { BLAST_COOLDOWN, BLAST_SOUND };
        break;
    case ROCKET:
        return { ROCKET_COOLDOWN, ROCKET_SOUND };
        break;
    case DIFFUSER:
        return { ROCKET_COOLDOWN, ROCKET_SOUND };
    case ROCKET_DOUBLE:
        return { ROCKET_COOLDOWN, ROCKET_SOUND };
    case LAZER:
        return { LAZER_COOLDOWN, BLAST_SOUND };
        break;
    default:
        return { BLAST_COOLDOWN, BLAST_SOUND };
    }
}

AmmoParams getAmmoParamsByGunType(GunType type)
{
    switch (type)
    {
    case BLAST:
        return 
        { 
            BLAST_AMMO_SPEED, 
            BLAST_AMMO_TEXTURE_PARAMS, 
            BLAST_AMMO_LAUNCH_TEXTURE_PARAMS,
            BLAST_AMMO_EXPLOSION_TEXTURE_PARAMS,
            BLAST_AMMO_COLLIDER,
            COLLIDABLE_PROJECTILE_BLAST,
        };
    case DIFFUSER:
        return
        {
            DIFFUSER_AMMO_SPEED,
            ROCKET_AMMO_TEXTURE_PARAMS,
            ROCKET_AMMO_TEXTURE_PARAMS,
            ROCKET_AMMO_EXPLOSION_TEXTURE_PARAMS,
            ROCKET_AMMO_COLLIDER,
            COLLIDABLE_PROJECTILE_ROCKET
        };
    //case LAZER:
    //    return 
    //    { 
    //        LAZER_AMMO_SPEED, 
    //        LAZER_AMMO_TEXTURE_PARAMS, 
    //        LAZER_AMMO_COLLIDER 
    //    };
    default:
        return 
        { 
            ROCKET_AMMO_SPEED, 
            ROCKET_AMMO_TEXTURE_PARAMS, 
            ROCKET_AMMO_LAUNCH_TEXTURE_PARAMS,
            ROCKET_AMMO_EXPLOSION_TEXTURE_PARAMS,
            ROCKET_AMMO_COLLIDER,
            COLLIDABLE_PROJECTILE_ROCKET,
        };
    }
}

ShipParams getShipParams(const ShipType type)
{
    switch (type)
    {
    case SONIC_A:
        return
        {
            SONIC_A,
            SONIC_A_SHIP,               // sprite 
            SONIC_A_SHIP_EXPLOSION,     // explosion 
            { BLAST },                  // gunType 
            SONIC_A_SPEED,              // maxSpeed 
            THIN_SHIP_ARMOR,            // armor 
            THIN_SHIP_HEALTH,           // health 
            SONIC_A_COLLIDERS_DEFAULT,  // colliders 
            GAME_OVER_SOUND             // explosionSound 
        };
    case SONIC_B:
        return
        {
            SONIC_B,
            SONIC_B_SHIP,               // sprite 
            SONIC_B_SHIP_EXPLOSION,     // explosion 
            { BLAST },                  // gunType 
            SONIC_A_SPEED,              // maxSpeed 
            THIN_SHIP_ARMOR,            // armor 
            THIN_SHIP_HEALTH,           // health 
            SONIC_A_COLLIDERS_DEFAULT,  // colliders 
            GAME_OVER_SOUND             // explosionSound 
        };
    case SONIC_C:
        return
        {
            SONIC_C,
            SONIC_C_SHIP,               // sprite 
            SONIC_C_SHIP_EXPLOSION,     // explosion 
            { BLAST },                  // gunType 
            SONIC_A_SPEED,              // maxSpeed 
            THIN_SHIP_ARMOR,            // armor 
            THIN_SHIP_HEALTH,           // health 
            SONIC_A_COLLIDERS_DEFAULT,  // colliders 
            GAME_OVER_SOUND             // explosionSound 
        };
    case PIRATE_A:
        return
        {
            PIRATE_A,
            PIRATE_A_SHIP, 
            PIRATE_A_SHIP_EXPLOSION, 
            { ROCKET },
            PIRATE_A_SPEED, 
            THIN_SHIP_ARMOR, 
            THIN_SHIP_HEALTH, 
            PIRATE_A_COLLIDERS_DEFAULT, 
            PIRATE_EXPLOSION_SOUND
        };
    case BOSS_A:
        return
        {
            BOSS_A,
            BOSS_A_SHIP,
            BOSS_A_SHIP_EXPLOSION,
            { ROCKET, DIFFUSER, ROCKET_DOUBLE },
            BOSS_A_SPEED,
            STRONG_SHIP_ARMOR,
            STRONG_SHIP_HEALTH,
            BOSS_A_COLLIDERS_DEFAULT,
            PIRATE_EXPLOSION_SOUND
        };
    }
}

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

int getRadius(GunType type)
{
    AmmoParams params = getAmmoParamsByGunType(type);
    return params.texture.imageH > params.texture.imageW ? params.texture.imageH / 2 : params.texture.imageW / 2;
}

bool isOutside(Vector2 pos)
{
    bool isOutside = pos.y < 0
        || pos.x < 0
        || pos.y > WINDOWED_HEIGHT
        || pos.x > WINDOWED_WIDTH;

    return isOutside;
};
