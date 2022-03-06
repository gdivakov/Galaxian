#include "EnemyShip.h"
#include <math.h>

double degreesToRadians(double degrees);

EnemyShip::EnemyShip(const App* p_system, std::string path, ShipParams params, PlayerShip& player) :
	Ship(p_system, path, params)
{
	playerRect = player.getRect();
	rotate = 0;
	inView = false;
	dir = Vector2(rect.x + rect.w/2, rect.y);
}

EnemyShip::~EnemyShip()
{
	playerRect = NULL;
}

void EnemyShip::onBeforeRender()
{
	gun.onBeforeRender();
	move();
	std::vector<SDL_Rect>& shipClips = getClips();
	SDL_Rect* currentClip = &shipClips[frame / shipClips.size()];
	render(rect.x, rect.y, currentClip, rotate, NULL);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, rect.x + rect.w/2, rect.y + rect.h/2, dir.x, dir.y); // Direction line
	SDL_RenderDrawLine(renderer, playerRect->x + playerRect->w/2, playerRect->y + playerRect->h/2, playerRect->x + playerRect->w/2, playerRect->y);
	
	if (inView)
	{
		SDL_RenderDrawLine(renderer, dir.x, dir.y, playerRect->x + playerRect->w/2, playerRect->y + playerRect->h / 2);
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
			rotate -= rotateVal;
			// Update direction
			pos = Vector2(rect.x + rect.w / 2, rect.y + rect.h / 2); // Rotation center
			dir = dir - pos;

			dir = Vector2(
				dir.x * cos(degreesToRadians(rotateVal)) + dir.y * sin(degreesToRadians(rotateVal)),
				dir.x * -sin(degreesToRadians(rotateVal)) + dir.y * cos(degreesToRadians(rotateVal))
			);
			dir = dir + pos;
			checkDirections();
			isInView();

			break;
		case SDLK_e:
			rotate += rotateVal;

			pos = Vector2(rect.x + rect.w / 2, rect.y + rect.h / 2);
			dir = dir - pos;

			dir = Vector2(
				dir.x * cos(degreesToRadians(rotateVal)) - dir.y * sin(degreesToRadians(rotateVal)),
				dir.x * sin(degreesToRadians(rotateVal)) + dir.y * cos(degreesToRadians(rotateVal))
			);
			dir = dir + pos;
			checkDirections();
			isInView();

			break;
		}
	}
}

double degreesToRadians(double degrees)
{
	return degrees * M_PI / 180;
}

void EnemyShip::checkDirections()
{ 
	// Todo: optimize by shifting player vector to enemy pos
	Vector2 posA(rect.x + rect.w / 2, rect.y + rect.h / 2); // Rotation center
	Vector2 relativeDirA = dir - posA;
	Vector2 relativeDirANorm = relativeDirA / Vector2::getDistance(dir, posA);

	Vector2 playerDir(playerRect->x + playerRect->w / 2, playerRect->y);
	Vector2 posB(playerRect->x + playerRect->w/2, playerRect->y + playerRect->h/2);
	Vector2 relativeDirB = playerDir - posB;
	Vector2 relativeDirBNorm = relativeDirB / Vector2::getDistance(playerDir, posB);
	
	float coef = relativeDirANorm.x* relativeDirBNorm.x + relativeDirANorm.y * relativeDirBNorm.y;
	
	if (coef == 1)
	{
		std::cout << "same dir" << std::endl;
	}
}

void EnemyShip::isInView()
{
	const float acceptableShift = 0.1;

	Vector2 posA(rect.x + rect.w/2, rect.y + rect.h /2);
	Vector2 relativeDirA = dir - posA;
	Vector2 relativeDirANorm = relativeDirA / Vector2::getDistance(dir, posA);
	//std::cout << playerRect->x << ": " << playerRect->y << std::endl;
	Vector2 playerShip(playerRect->x + playerRect->w / 2, playerRect->y + playerRect->h / 2);
	Vector2 playerShipDir = playerShip - posA;
	Vector2 playerShipNorm = playerShipDir / Vector2::getDistance(playerShip, posA);


	float coef = relativeDirANorm.x * playerShipNorm.x + relativeDirANorm.y * playerShipNorm.y;


	if (coef >= 1 - acceptableShift)
	{
		std::cout << coef << std::endl;

		inView = true;
	}
	else {
		inView = false;
	}
}
