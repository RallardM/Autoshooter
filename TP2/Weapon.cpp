#include <raylib.h>

#include "Weapon.h"
#include "MathUtils.h"
#include <iostream>

void Weapon::OnStart()
{
	// Generate a random color for each gun squares with caps 10 to 240 to not have total black or total white
	m_color = { (unsigned char)GetRandomValue(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE), (unsigned char)GetRandomValue(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE), (unsigned char)GetRandomValue(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE), 255 };
}

void Weapon::IncreaseRate()
{
	m_weaponInfos.m_attackRate *= HALF;
}

void Weapon::IncreaseProjectileDamage()
{
	m_weaponInfos.m_projectileInfos.DAMAGE *= P_INCREASE_DAMAGE_FACTOR;
	std::cout << "Projectile damage doubled : " << m_weaponInfos.m_projectileInfos.DAMAGE << std::endl;
}

void Weapon::IncreaseProjectileSize()
{
	m_weaponInfos.m_projectileInfos.RADIUS *= P_INCREASE_DAMAGE_FACTOR;
}

void Weapon::FollowPosition(Vector2 newPosition)
{
	m_position = newPosition;
}