#pragma once
#include <vector>
#include "ShipConsts.h"

class BezierPath
{
private: 
	std::vector<BezierCurve> curves;
	std::vector<int> samples;
public:
	BezierPath();
	void addCurve(BezierCurve nextCurve, int sampleCount);
	void addPath(std::vector<Vector2>* preparedPath);
};

