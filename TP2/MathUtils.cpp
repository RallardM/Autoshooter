#include "MathUtils.h"
#include <cmath>

const float FULL_CIRCLE = 2.0f * PI;

float Vector2Distance(const Vector2& firstVector, const Vector2& secondVector)
{
	float distanceInX = secondVector.x - firstVector.x;
	float distanceInY = secondVector.y - firstVector.y;
	return static_cast<float>(sqrt(distanceInX * distanceInX + distanceInY * distanceInY));
}

float GetMagnitude(Vector2 vector)
{
	return static_cast<float>(sqrt(vector.x * vector.x + vector.y * vector.y));
}