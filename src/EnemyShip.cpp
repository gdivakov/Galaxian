#include "EnemyShip.h"
#include <math.h>

double degreesToRadians(double degrees); // todo: set in consts.h

EnemyShip::EnemyShip(
	const App* p_system, 
	std::string p_path, 
	ShipParams& params, 
	PlayerShip& player
) :
	Ship(p_system, p_path, params)
{
	playerRect = player.getRect();
	rotation = 0;
	currentWaypoint = 0;
	inView = false;

	BezierPath* bezierPath = new BezierPath();

	const int WAYPOINT_NUMBER = 3; // Todo: edit here

	for (int i = 0; i < params.pathCurves.size(); i++)
	{
		bezierPath->addCurve(params.pathCurves[i], WAYPOINT_NUMBER);
	}

	bezierPath->setPath(&path);

	delete bezierPath;
	
	rect.x = path[0].x;
	rect.y = path[0].y;

	Vector2 top(rect.x + rect.w / 2, rect.y);
	Vector2 center(rect.x + rect.w / 2, rect.y + rect.h / 2);

	dir = top - center;
}

EnemyShip::~EnemyShip()
{
	playerRect = NULL;
}

void EnemyShip::followPath()
{
	Vector2 pos = Vector2(rect.x, rect.y);

	if (currentWaypoint < path.size() && Vector2::getDistance(path[currentWaypoint], pos) < EPSILON)
	{
		currentWaypoint++;
	}
	else if (currentWaypoint < path.size())
	{
		Vector2 moveDir = path[currentWaypoint] - pos;
		Vector2 normMoveDir = moveDir / Vector2::getDistance(path[currentWaypoint], pos);
		pos = pos + normMoveDir * maxVelocity/2;

		rotate(atan2(moveDir.y, moveDir.x) * RAD_TO_DEG + 90.0f);

		rect.x = pos.x;
		rect.y = pos.y;
	}
	else {
		// finish path
	}
}

void EnemyShip::onBeforeRender()
{
	gun.onBeforeRender();

	followPath();
	move();

	std::vector<SDL_Rect>& shipClips = getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
	Vector2 dirToRender = dir + Vector2(rect.x, rect.y);

	render(rect.x - rect.w/2, rect.y - rect.h/2, currentClip, rotation, NULL);
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderDrawLine(renderer, rect.x, rect.y, dirToRender.x, dirToRender.y); // Direction line

	if (inView)
	{
		SDL_RenderDrawLine(renderer, dirToRender.x, dirToRender.y, playerRect->x + playerRect->w/2, playerRect->y + playerRect->h / 2);
	}

	//displayPath();
}

void EnemyShip::rotate(int r)
{
	if (r - rotation > 0) {
		// clockwise
		updateDirection(r - rotation);
	}
	else
	{
		updateDirection(abs(r - rotation), false);
	}

	rotation = r;

	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	if (rotation < 0.0f)
	{
		rotation += 360.0f;
	}
}

void EnemyShip::onAfterRender()
{
	gun.onAfterRender();

	int clipLength = getClips().size();

	++frame;
	if (frame / clipLength >= clipLength)
	{
		frame = 0;
	}
}

void EnemyShip::handleEvent(SDL_Event& e)
{
	int rotateVal = 10;
	Vector2 pos;

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			rotate(rotation - rotateVal);

			//checkDirections();
			isInView();

			break;
		case SDLK_e:
			rotate(rotation + rotateVal);

			//checkDirections();
			isInView();

			break;
		}
	}
}

double degreesToRadians(double degrees)
{
	return degrees * M_PI / 180;
}

void EnemyShip::isInView()
{
	const float acceptableShift = 0.1;

	Vector2 pos(rect.x + rect.w/2, rect.y + rect.h/2);
	Vector2 enemyTop(rect.x + rect.w / 2, rect.y);
	Vector2 enemyNorm = dir / Vector2::getDistance(enemyTop, pos);

	Vector2 playerCenter(playerRect->x + playerRect->w / 2, playerRect->y + playerRect->h / 2);
	Vector2 playerDir = playerCenter - pos;
	Vector2 playerNorm = playerDir / Vector2::getDistance(playerCenter, pos);

	float coef = enemyNorm.x * playerNorm.x + enemyNorm.y * playerNorm.y;

	inView = coef >= 1 - acceptableShift;
}

void EnemyShip::displayPath()
{
	int pathIdx = 0;

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

void EnemyShip::updateDirection(float rotateVal, bool clockwise)
{
	if (clockwise)
	{
		dir = Vector2(
			dir.x * cos(degreesToRadians(rotateVal)) - dir.y * sin(degreesToRadians(rotateVal)),
			dir.x * sin(degreesToRadians(rotateVal)) + dir.y * cos(degreesToRadians(rotateVal))
		);
	}
	else
	{
		dir = Vector2(
			dir.x * cos(degreesToRadians(rotateVal)) + dir.y * sin(degreesToRadians(rotateVal)),
			dir.x * -sin(degreesToRadians(rotateVal)) + dir.y * cos(degreesToRadians(rotateVal))
		);
	}
}

//void EnemyShip::checkDirections()
//{ 
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