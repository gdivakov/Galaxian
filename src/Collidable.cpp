#include "Collidable.h"

void removeFromArray(Collidable::Collidables& arr, Collidable* enColl) // Todo: Replace by Template Function
{
    auto removeIter = remove(arr.begin(), arr.end(), enColl);
    arr.erase(removeIter, arr.end());
};

Collidable::Collidable(SDL_Renderer* p_renderer, CollidableType p_type, int wrapperRadius, Colliders p_colliders)
: colliders(p_colliders), renderer(p_renderer)
{
    type = p_type;
    rotation = 0;
    isCollided = false;
    collidedTo = NULL;
    isActive = true;
    wrapperCollider.r = wrapperRadius;
};

Collidable::~Collidable()
{
    collidedTo = NULL;
    renderer = NULL;
}

void Collidable::showColliders()
{
    // Display wrapper & inner colliders
    DrawCircle(renderer, wrapperCollider.pos.x, wrapperCollider.pos.y, wrapperCollider.r);

    Colliders preparedColliders = colliders;
    rotateColliders(preparedColliders, rotation);
    addVectorToCollider(preparedColliders, wrapperCollider.pos);

    for (int i = 0; i < preparedColliders.size(); i++)
    {
        renderCollider(renderer, preparedColliders[i]);
    }
}

bool Collidable::checkCollision()
{
    Collidables possibleCollidables;

    for (int i = 0; i < linkedCollidables.size(); i++)
    {
        Collidable* coll = linkedCollidables[i];

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
        bool hasRectColliders = colliders.size();
        bool enemyHasRectColliders = possibleCollidables[i]->colliders.size();

        if (!hasRectColliders || !enemyHasRectColliders || checkRectCollision(possibleCollidables[i]))
        {
            // Circle collision check is enough if there are no rect colliders
            isCollided = true;
            possibleCollidables[i]->isCollided = true;
            possibleCollidables[i]->collidedTo = this;
            collidedTo = possibleCollidables[i];

            possibleCollidables[i]->handleCollided();
            handleCollided();
            break;
        }
    }

    return isCollided;
}

bool Collidable::checkRectCollision(Collidable* enemyCollider)
{
    Colliders preparedColliders = colliders;
    Colliders enemyColliders = enemyCollider->getColliders();
    Vector2 enemyToShip = wrapperCollider.pos - enemyCollider->wrapperCollider.pos;

    rotateColliders(enemyColliders, enemyCollider->rotation);
    rotateColliders(preparedColliders, rotation);

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

void Collidable::linkTo(Collidable* enColl)
{ 
    linkedCollidables.push_back(enColl);
    enColl->linkedCollidables.push_back(this);
};

void Collidable::unlinkFrom() 
{    
    for (int i = 0; i < linkedCollidables.size(); i++)
    {
        removeFromArray(linkedCollidables[i]->linkedCollidables, this);
    }

    linkedCollidables.clear();
}