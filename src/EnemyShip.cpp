#include <math.h>

#include "EnemyShip.h"

const int WAYPOINT_NUMBER = 4; // Todo: edit here

EnemyShip::EnemyShip(
	LevelBase* p_level,
	ShipType type, 
	Ship* p_playerShip,
	std::vector<BezierCurve> pathCurves
) :
	Ship(p_level->getSystem(), getShipParams(type), p_level, true)
{
	player = p_playerShip;
	currentWaypoint = 0;
	inView = false;


	addPath(pathCurves);
	pos = path[0];
}

EnemyShip::~EnemyShip()
{
	player = NULL;
}

void EnemyShip::addPath(std::vector<BezierCurve> pathCurves)
{
	BezierPath* bezierPath = new BezierPath();

	for (int i = 0; i < pathCurves.size(); i++)
	{
		bezierPath->addCurve(pathCurves[i], WAYPOINT_NUMBER);
	}

	bezierPath->setPath(&path);

	delete bezierPath;
}

void EnemyShip::followPath(bool withDirRotation)
{
	if (currentWaypoint < path.size() && Vector2::getDistance(path[currentWaypoint], pos) < EPSILON)
	{
		currentWaypoint++; 
	}
	else if (currentWaypoint < path.size())
	{
		Vector2 moveDir = path[currentWaypoint] - pos;
		Vector2 normMoveDir = moveDir / Vector2::getDistance(path[currentWaypoint], pos);
		pos = pos + normMoveDir * maxSpeed/2;

		if (withDirRotation)
		{
			rotate(atan2(moveDir.y, moveDir.x) * RAD_TO_DEG + 90.0f);
		}
	}
	else 
	{
		currentWaypoint = 0; // Repeat path
	}
}

void EnemyShip::onBeforeRender()
{
	gun->onBeforeRender();

	if (!level->isPaused && !isAccelerated)
	{
		followPath();
		move();
		isInView();

		if (inView && isActive)
		{
			gun->isShooting = true;
		}
		else
		{
			gun->isShooting = false;
		}
	}

	std::vector<SDL_Rect>& shipClips = getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];

	render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);

	//showColliders();
	//displayPath();
}

void EnemyShip::handleEvent(SDL_Event& e)
{

	if (level->isPaused)
	{
		return;
	}

	gun->handleEvent(e);
}

void EnemyShip::displayPath()
{
	int pathIdx = 0;

	SDL_SetRenderDrawColor(Texture::renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	do {
		SDL_RenderDrawLine(
			Texture::renderer,
			path[pathIdx].x,
			path[pathIdx].y,
			path[pathIdx + 1].x,
			path[pathIdx + 1].y
		);
		pathIdx++;
	} while (pathIdx + 1 < path.size());
}

void EnemyShip::isInView()
{
	ShipRect playerRect = player->getRect();
	const float acceptableShift = 0.1;

	Vector2 enemyDir = getDirection(LOCAL);
	Vector2 zero(0, 0);
	Vector2 enemyNorm = enemyDir / Vector2::getDistance(zero, enemyDir);

	Vector2 playerToEnemyDir = playerRect.pos - pos;
	Vector2 playerToEnemyNorm = playerToEnemyDir / Vector2::getDistance(playerRect.pos, pos);

	float coef = enemyNorm.x * playerToEnemyNorm.x + enemyNorm.y * playerToEnemyNorm.y;
	inView = coef >= 1 - acceptableShift;
}

void EnemyShip::startAccelerate()
{
	isAccelerated = true;
	isActive = false;

	unlink();
}

void EnemyShip::accelerate()
{
	if (!isAccelerated)
	{
		return;
	}

	Vector2 addVel = Vector2(0, BG_SCROLLING_SPEED_ACCELERATED);
	pos += addVel;

	if (pos.y >= level->getSystem()->getWindowSize()->h)
	{
		level->getSpawner()->removeObject(this);
	}
}

//void EnemyShip::checkDirections()
//{ 
//	ShipRect playerRect = player->getRect();
// 
//	const float acceptableShift = 0.1;
//
//	Vector2 pos(rect.x + rect.w / 2, rect.y + rect.h / 2);
//	Vector2 enemyTop(rect.x + rect.w / 2, rect.y);
//	Vector2 enemyDir = dir;
//	Vector2	enemyNorm = enemyDir / Vector2::getDistance(enemyTop, pos);
//
//	Vector2 playerTop(playerRect->x + playerRect->w / 2, playerRect->y);
//	Vector2 playerPos(playerRect->x + playerRect->w/2, playerRect->y + playerRect->h/2);
//	Vector2 playerDir = playerTop - playerPos;
//	Vector2 playerNorm = playerDir / Vector2::getDistance(playerTop, playerPos);
//	
//	float coef = enemyNorm.x* playerNorm.x + enemyNorm.y * playerNorm.y;
//
//	if (coef >= 1 - acceptableShift)
//	{
//		std::cout << "same dir" << std::endl;
//	}
//}

//if (inView)
//{

//	ShipRect playerRect = player->getRect();

//	SDL_RenderDrawLine(
//		renderer,
//		dirToRender.x,
//		dirToRender.y,
//		playerRect.pos.x,
//		playerRect.pos.y
//	);
//}