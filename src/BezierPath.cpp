#include "BezierPath.h"

BezierPath::BezierPath()
{}

void BezierPath::addCurve(BezierCurve nextCurve, int sampleCount)
{
	curves.push_back(nextCurve);
	samples.push_back(sampleCount);
}

void BezierPath::setPath(std::vector<Vector2>* preparedPath)
{
	for (int i = 0; i < curves.size(); i++)
	{
		for (float t = 0.0f; t < 1.0f; t += (1.0f / samples[i]))
		{
			preparedPath->push_back(curves[i].getPoint(t));
		}
	}
}