#include <raylib.h>
#include <iostream>

#include "Weapon.h"
#include "MathUtils.h"
#include "Globals.h"

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
	// Generate a random color for each gun squares with caps 30 to 200 to not have total black or total white
	m_color = { (unsigned char)GetRandomValue(
		MIN_COLOR_CHANNEL_VALUE, MAX_COLOR_CHANNEL_VALUE),
		(unsigned char)GetRandomValue(
			MIN_COLOR_CHANNEL_VALUE, MAX_COLOR_CHANNEL_VALUE), 
		(unsigned char)GetRandomValue(
			MIN_COLOR_CHANNEL_VALUE, MAX_COLOR_CHANNEL_VALUE), 
		FULL_ALPHA_VALUE };
}

void Weapon::IncreaseRate()
{
	m_weaponInfos.m_attackRate *= HALF;
}

void Weapon::IncreaseProjectileDamage()
{
	m_weaponInfos.m_projectileInfos.DAMAGE *= INCREASE_PROJECTILE_FACTOR;
	std::cout << "Projectile damage doubled : " << m_weaponInfos.m_projectileInfos.DAMAGE << std::endl;
}

void Weapon::IncreaseProjectileSize()
{
	m_weaponInfos.m_projectileInfos.RADIUS *= INCREASE_PROJECTILE_FACTOR;
}

void Weapon::FollowPosition(const Vector2& newPosition)
{
	m_position = newPosition;
}