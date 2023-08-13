#include <raylib.h>

#include "Weapon.h"
#include "MathUtils.h"
#include <iostream>

void Weapon::IncreaseRate()
{
	m_weaponInfos.m_attackRate *= HALF;
}

void Weapon::IncreaseProjectileDamage()
{
	m_weaponInfos.m_projectileInfos.DAMAGE *= 2.0f;
}

void Weapon::IncreaseProjectileSize()
{
	m_weaponInfos.m_projectileInfos.RADIUS *= 2.0f;
}

void Weapon::FollowPosition(Vector2 newPosition)
{
	m_position = newPosition;
}