#include "MathUtils.h"
#include <cmath>

const float FULL_CIRCLE = 2.0f * PI;
const float FOURTH = 0.25f;
const float EIGHTH = 0.125f;
const float HALF = 0.5f;
const float THREE_FOURTH = 0.75f;

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

Vector2 SubstractVectors(Vector2 firstVector, Vector2 secondVector)
{
	Vector2 result;
	result.x = firstVector.x - secondVector.x;
	result.y = firstVector.y - secondVector.y;
	return result;
}