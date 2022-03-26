#pragma once
#include <vector>
#include "Consts.h"

class BezierPath
{
private: 
	std::vector<BezierCurve> curves;
	std::vector<int> samples;
public:
	BezierPath();
	void addCurve(BezierCurve nextCurve, int sampleCount);
	void setPath(std::vector<Vector2>* preparedPath);
};

