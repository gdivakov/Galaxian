#include <math.h>

#include "Vector2.h"
#include "Consts.h"

Vector2::Vector2(float p_x, float p_y)
{
	x = p_x;
	y = p_y;
}

float Vector2::getDistance(Vector2& vec1, Vector2& vec2)
{
	Vector2 sub = vec2.operator-(vec1);
	float res = sqrt(pow(sub.x, 2) + pow(sub.y, 2));

	return res;
}

float Vector2::getDistanceSquared(Vector2& vec1, Vector2& vec2)
{
	Vector2 sub = vec2.operator-(vec1);
	float res = pow(sub.x, 2) + pow(sub.y, 2);

	return res;
}

void Vector2::log()
{
	std::cout << "x: " << this->x << ", " << "y: " << this->y << std::endl;
}

Vector2 Vector2::operator+=(Vector2& v)
{
	Vector2 nextVector(this->x + v.x, this->y + v.y);
	this->x = nextVector.x;
	this->y = nextVector.y;

	return nextVector;
}

Vector2 Vector2::operator-=(Vector2& v)
{
	Vector2 nextVector(this->x - v.x, this->y - v.y);
	this->x = nextVector.x;
	this->y = nextVector.y;

	return nextVector;
}

Vector2 Vector2::getRotatedVector(Vector2& v, int angle)
{
	float rotationRad = angle * DEG_TO_RAD;

	Vector2 nextVector(
		v.x * cos(rotationRad) - v.y * sin(rotationRad),
		v.x * sin(rotationRad) + v.y * cos(rotationRad)
	);

	return nextVector;
}

bool isOutside(Vector2 pos)
{
	bool isOutside = pos.y < 0
		|| pos.x < 0
		|| pos.y > WINDOWED_HEIGHT
		|| pos.x > WINDOWED_WIDTH;

	return isOutside;
};