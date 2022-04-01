#pragma once
#include <SDL.h>
#include <iostream>

class Vector2
{
public: 
	float x;
	float y;
	Vector2(float x = 0, float y = 0);
	Vector2 operator+(Vector2 v) { return Vector2(this->x + v.x, this->y + v.y); };
	Vector2 operator+=(Vector2 v);
	Vector2 operator-(Vector2 v) { return Vector2(this->x - v.x, this->y - v.y); };
	Vector2 operator*(float v) { return Vector2(this->x * v, this->y * v); };
	Vector2 operator/(float v) { return Vector2(this->x / v, this->y / v); };
	static float getDistance(Vector2& vec1, Vector2& vec2);
	static float getDistanceSquared(Vector2& vec1, Vector2& vec2);
	void log();
	friend Vector2 operator*(float n, Vector2& v) { return v * n; }
};