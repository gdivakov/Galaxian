#include <math.h>

#include "Consts.h"
#include "EnemyShip.h"

EnemyShip::EnemyShip(
	const App* p_system, 
	LevelBase* p_level,
	ShipParams& params, 
	PlayerShip* p_player,
	std::vector<BezierCurve> pathCurves
) :
	Ship(p_system, params, p_level, p_player),
	player(p_player)
{
	currentWaypoint = 0;
	inView = false;
	const int WAYPOINT_NUMBER = 3; // Todo: edit here

	BezierPath* bezierPath = new BezierPath();

	for (int i = 0; i < pathCurves.size(); i++)
	{
		bezierPath->addCurve(pathCurves[i], WAYPOINT_NUMBER);
	}

	bezierPath->setPath(&path);

	delete bezierPath;
	
	pos = path[0];

	Vector2 top(pos.x, pos.y);
	Vector2 center = pos + Vector2(0, size.h / 2);

	dir = top - center;
}

void EnemyShip::followPath()
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

		rotate(atan2(moveDir.y, moveDir.x) * RAD_TO_DEG + 90.0f);
	}
	else {
		// finish path
	}
}

void EnemyShip::onBeforeRender()
{
	gun->onBeforeRender();

	if (!level->isPaused)
	{
		followPath();
		move();
	}

	std::vector<SDL_Rect>& shipClips = getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
	Vector2 dirToRender = Vector2::getRotatedVector(dir, rotation) + pos;

	render(pos - Vector2(size.w / 2, size.h / 2), currentClip, rotation, NULL);
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//showColliders();
	SDL_RenderDrawLine(renderer, pos.x, pos.y, dirToRender.x, dirToRender.y);
	
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

	Colliders preparedColliders2 = getColliders(WORLD, collidedShip);

	for (int i = 0; i < preparedColliders2.size(); i++)
	{
		SDL_RenderDrawLine(renderer, preparedColliders2[i].a.x, preparedColliders2[i].a.y, preparedColliders2[i].b.x, preparedColliders2[i].b.y);
		SDL_RenderDrawLine(renderer, preparedColliders2[i].b.x, preparedColliders2[i].b.y, preparedColliders2[i].c.x, preparedColliders2[i].c.y);
		SDL_RenderDrawLine(renderer, preparedColliders2[i].c.x, preparedColliders2[i].c.y, preparedColliders2[i].d.x, preparedColliders2[i].d.y);
		SDL_RenderDrawLine(renderer, preparedColliders2[i].d.x, preparedColliders2[i].d.y, preparedColliders2[i].a.x, preparedColliders2[i].a.y);
	}

	//displayPath();
}

void EnemyShip::rotate(int r)
{
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

void EnemyShip::handleEvent(SDL_Event& e)
{

	if (level->isPaused)
	{
		return;
	}

	int rotateVal = 10;

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

void EnemyShip::isInView()
{
	ShipRect playerRect = player->getRect();

	const float acceptableShift = 0.1;

	Vector2 enemyCenter(pos.x + size.w/2, pos.y + size.h/2);
	Vector2 enemyTop(enemyCenter.x + size.w / 2, enemyCenter.y);
	Vector2 enemyNorm = dir / Vector2::getDistance(enemyTop, enemyCenter);

	Vector2 playerCenter(playerRect.pos.x + playerRect.size.w / 2, playerRect.pos.y + playerRect.size.h / 2);
	Vector2 playerDir = playerCenter - enemyCenter;
	Vector2 playerNorm = playerDir / Vector2::getDistance(playerCenter, enemyCenter);

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