#pragma once
#include <raylib.h>

extern const float FULL_CIRCLE; 

// TODO end of production verify if all '/ 2' '/ 4' '/ 3' have been replaced by this
extern const float FOURTH; // 1 / 4 or * 0.25
extern const float EIGHTH; // 1 / 8 or * 0.125
extern const float HALF; // 1 / 2 or * 0.5
extern const float THREE_FOURTH; // 3 / 4 or * 0.75
extern const float HUNDRETH; // 1 / 100 or * 0.01
extern const int EVEN;
extern const int DOUBLE;

extern float GetFloatDistanceBetweenTwoVects(const Vector2& firstVector, const Vector2& secondVector);
extern Vector2 GetVectDistanceBetweenTwoVects(const Vector2& firstVector, const Vector2& secondVector);
extern float GetMagnitude(const Vector2& vector);
extern Vector2 SubstractVectors(const Vector2& firstVector, const Vector2& secondVector);