#include <math.h>
#include "EnemyShip.h"
#include "SettingsConsts.h"

const int WAYPOINT_NUMBER = 4;

EnemyShip::EnemyShip(
	LevelBase* p_level,
	ShipType type, 
	std::vector<BezierCurve> pathCurves
) :
	Ship(p_level->getSystem(), SHIP_PARAMS.at(type), p_level)
{
	currentWaypoint = 0;
	inView = false;

	addPath(pathCurves);
	pos = path[0];
}

void EnemyShip::addPath(std::vector<BezierCurve> pathCurves)
{
	BezierPath* bezierPath = new BezierPath();

	for (int i = 0; i < pathCurves.size(); i++)
	{
		bezierPath->addCurve(pathCurves[i], WAYPOINT_NUMBER);
	}

	bezierPath->addPath(&path);

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
		bool hardModeSelected = readSettingsConfig()[SETTINGS_FIELDS::DIFFICULTY];

		if (!hardModeSelected || level->getPlayer() == nullptr)
		{
			currentWaypoint = 0; // Repeat path
			return;
		}

		// Chase the player
		Vector2 pointStart(path[path.size() - 1]);
		Vector2 pointEnd(level->getPlayer()->getRect().pos);
		Vector2 centerDir((pointEnd - pointStart)/2);

		Vector2 circle45 = Vector2::getRotatedVector(centerDir, 45);

		std::vector<BezierCurve> curves = {{ pointStart, pointStart + circle45, pointStart + circle45, pointEnd }};
		addPath(curves);
	}
}

void EnemyShip::onBeforeRender()
{
	gun->handleRender();

	if (!level->isPaused && !level->getIsAccelerated())
	{
		if (isActive)
		{
			followPath();
			move();
		}

		if (isPlayerInView() && isActive && level->getPlayer() != nullptr)
		{
			gun->setIsShooting(true);
		}
		else
		{
			gun->setIsShooting(false);
		}
	}

	std::vector<SDL_Rect>& shipClips = getTexture()->getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
	Size& size = getTexture()->size;

	getTexture()->render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
	//showColliders();
	//displayPath();
}

void EnemyShip::displayPath()
{
	int pathIdx = 0;

	SDL_Renderer* renderer = level->getSystem()->getRenderer();
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	do {
		SDL_RenderDrawLine(
			renderer,
			path[pathIdx].x,
			path[pathIdx].y,
			path[pathIdx + 1].x,
			path[pathIdx + 1].y
		);
		pathIdx++;
	} while (pathIdx + 1 < path.size());
}

bool EnemyShip::isPlayerInView()
{
	if (level->getPlayer() == nullptr)
	{
		return false;
	}
	ShipRect playerRect = level->getPlayer()->getRect();
	const float acceptableShift = 0.1;

	Vector2 enemyDir = getDirection(LOCAL);
	Vector2 zero(0, 0);
	Vector2 enemyNorm = enemyDir / Vector2::getDistance(zero, enemyDir);

	Vector2 playerToEnemyDir = playerRect.pos - pos;
	Vector2 playerToEnemyNorm = playerToEnemyDir / Vector2::getDistance(playerRect.pos, pos);

	float coef = enemyNorm.x * playerToEnemyNorm.x + enemyNorm.y * playerToEnemyNorm.y;
	inView = coef >= 1 - acceptableShift;

	return inView;
}

void EnemyShip::onAccelerate()
{
	Ship::onAccelerate();

	isActive = false;
	unlink();
}

void EnemyShip::handleAcceleration()
{
	if (!level->getIsAccelerated())
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