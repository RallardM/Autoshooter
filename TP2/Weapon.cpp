#include <raylib.h>

#include "Weapon.h"
#include "MathUtils.h"
#include <iostream>

unsigned short int Weapon::s_weaponId = 0;

Weapon::Weapon()
{
	m_weaponId = s_weaponId++;
	std::cout << "Weapon constructor called. ID = " << m_weaponId << std::endl;
}

Weapon::~Weapon()
{
	std::cout << "Weapon destructor called. ID = " << m_weaponId << std::endl;
}

void Weapon::OnStart()
{
	// Generate a random color for each gun squares with caps 10 to 240 to not have total black or total white
	m_color = { (unsigned char)GetRandomValue(10, 240), (unsigned char)GetRandomValue(10, 240), (unsigned char)GetRandomValue(10, 240), 255 };
}

void Weapon::IncreaseRate()
{
	m_weaponInfos.m_attackRate *= HALF;
}

void Weapon::IncreaseProjectileDamage()
{
	m_weaponInfos.m_projectileInfos.DAMAGE *= 2.0f;
	std::cout << "Projectile damage doubled : " << m_weaponInfos.m_projectileInfos.DAMAGE << std::endl;
}

void Weapon::IncreaseProjectileSize()
{
	m_weaponInfos.m_projectileInfos.RADIUS *= 2.0f;
}

void Weapon::FollowPosition(Vector2& newPosition)
{
	m_position = newPosition;
}