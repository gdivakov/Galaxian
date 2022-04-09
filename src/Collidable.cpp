#include "Collidable.h"

Collidable::Collidable(SDL_Renderer* p_renderer, Colliders p_colliders, int wrapperRadius)
: colliders(p_colliders), collidableRenderer(p_renderer)
{
    collidableRotation = 0;
    isCollided = false;
    collidedTo = NULL;
    wrapperCollider.r = wrapperRadius;
};

void Collidable::showColliders()
{
    // Display wrapper & inner colliders
    DrawCircle(collidableRenderer, wrapperCollider.pos.x, wrapperCollider.pos.y, wrapperCollider.r);

    Colliders preparedColliders = colliders;
    rotateColliders(preparedColliders, collidableRotation);
    addVectorToCollider(preparedColliders, wrapperCollider.pos);

    for (int i = 0; i < preparedColliders.size(); i++)
    {
        renderCollider(collidableRenderer, preparedColliders[i]);
    }
}

Collidable::~Collidable()
{
    //deregisterCollidable from enemyCollidable array where collidable is "self"
}

bool Collidable::checkCollision()
{
    if (isCollided)
    {
        return isCollided;
    }

    std::vector<Collidable*> possibleCollidables;

    for (int i = 0; i < enemyCollidables.size(); i++)
    {
        Collidable* coll = enemyCollidables[i];

        int distanceSquared = Vector2::getDistanceSquared(coll->wrapperCollider.pos, wrapperCollider.pos);
        int radiusesSquared = pow(wrapperCollider.r + coll->wrapperCollider.r, 2);

        if (distanceSquared > radiusesSquared)
        {
            continue;
        }

        possibleCollidables.push_back(coll);
    }

    if (!possibleCollidables.size())
    {
        return false;
    }

    for (int i = 0; i < possibleCollidables.size(); i++)
    {
        if (checkRectCollision(possibleCollidables[i]))
        {
            isCollided = true;
            collidedTo = enemyCollidables[i];

            collidedTo->isCollided = true;

            handleCollided();
            // Remove collidable from ship list of enemy collidables
            deregisterEnemyCollidable(possibleCollidables[i]);
            possibleCollidables[i]->handleCollided();
        }
    }

    return isCollided;
}

bool Collidable::checkRectCollision(Collidable* enemyCollider)
{
    Colliders preparedColliders = colliders;
    Colliders enemyColliders = enemyCollider->getColliders();
    Vector2 enemyToShip = wrapperCollider.pos - enemyCollider->wrapperCollider.pos;

    rotateColliders(enemyColliders, enemyCollider->collidableRotation);
    rotateColliders(preparedColliders, collidableRotation);

    addVectorToCollider(preparedColliders, enemyToShip);

    for (int i = 0; i < enemyColliders.size(); i++)
    {
        for (int k = 0; k < preparedColliders.size(); k++)
        {
            // SAT alghoritm 
            if (checkOverlapSAT(preparedColliders[k], enemyColliders[i]))
            {
                return true;
            }
        }
    }

    return false;
}

void Collidable::registerEnemyCollidable(Collidable* enemyCollider)
{ 
    enemyCollidables.push_back(enemyCollider);
};

void Collidable::deregisterEnemyCollidable(Collidable* collidable) 
{
    auto removeIter = remove(enemyCollidables.begin(), enemyCollidables.end(), collidable);
    enemyCollidables.erase(removeIter, enemyCollidables.end());
}

//Colliders Collidable::getColliders(Space space)
//{
    //Colliders preparedColliders = colliders;
    //CollidableDesc desc = getCollidableDesc();
    //rotateColliders(preparedColliders, desc.rotation);

    //if (parent == NULL)
    //{
    //    return space == LOCAL ? colliders : addVectorToCollider(preparedColliders, pos);
    //}

    //if (parent) // Return position relative to the parent
    //{
    //    Vector2 parentToShip = pos - parent->pos;
    //    addVectorToCollider(preparedColliders, parentToShip);

    //    return space == LOCAL ? preparedColliders : addVectorToCollider(preparedColliders, parent->pos);
    //}
//}