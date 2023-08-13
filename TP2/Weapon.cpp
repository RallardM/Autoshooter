#include <raylib.h>

#include "Weapon.h"
#include <iostream>

void Weapon::FollowPosition(Vector2 newPosition)
{
	m_position = newPosition;
}