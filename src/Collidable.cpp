#include "Collidable.h"

Collidable::Collidable(SDL_Renderer* p_renderer, Colliders p_colliders, int wrapperRadius)
: colliders(p_colliders), collidableRenderer(p_renderer)
{
    collidableRotation = 0;
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

bool Collidable::checkCollision()
{
    std::vector<Collidable*> possibleColliders;
    bool isCollided = false;

    for (int i = 0; i < enemyColliders.size(); i++)
    {
        Collidable* coll = enemyColliders[i];

        int distanceSquared = Vector2::getDistanceSquared(coll->wrapperCollider.pos, wrapperCollider.pos);
        int radiusesSquared = pow(wrapperCollider.r + coll->wrapperCollider.r, 2);

        if (distanceSquared > radiusesSquared)
        {
            continue;
        }

        possibleColliders.push_back(coll);
    }

    if (!possibleColliders.size())
    {
        return false;
    }

    for (int i = 0; i < possibleColliders.size(); i++)
    {
        if (checkRectCollision(possibleColliders[i]))
        {
            isCollided = true;
            possibleColliders[i]->handleCollided();
        }
    }

    return isCollided;
}

bool Collidable::checkRectCollision(Collidable* enemyCollider)
{
    Colliders preparedColliders = Colliders(colliders);
    Colliders enemyColliders = Colliders(enemyCollider->getColliders());
    Vector2 enemyToShip = wrapperCollider.pos - enemyCollider->wrapperCollider.pos;

    rotateColliders(enemyColliders, enemyCollider->collidableRotation);
    rotateColliders(preparedColliders, collidableRotation);

    addVectorToCollider(preparedColliders, enemyToShip);


    for (int i = 0; i < enemyColliders.size(); i++)
    {
        for (int k = 0; k < preparedColliders.size(); k++)
        {
            // SAT alghoritm 
            if (checkOverlapSAT(preparedColliders[i], enemyColliders[k]))
            {
                return true;
            }
        }
    }

    return false;
}

void Collidable::deregisterEnemyCollider(Collidable* enemyCollider) {
    auto removeIter = remove(enemyColliders.begin(), enemyColliders.end(), enemyCollider);
    enemyColliders.erase(removeIter, enemyColliders.end());
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