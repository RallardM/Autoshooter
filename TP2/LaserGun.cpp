#include <iostream>
#include "LaserGun.h"
#include "Globals.h"
#include "GameObjectPool.h"

float LaserGun::s_uiOffsetRight = 0.0f;

unsigned short int LaserGun::s_id = 0;

LaserGun::LaserGun()
{
	m_id = s_id++;
	std::cout << "LaserGun constructor called. ID = " << m_id << std::endl;
}

LaserGun::~LaserGun()
{
	std::cout << "LaserGun destructor called. ID = " << m_id << std::endl;
}

void LaserGun::Fire()
{
	m_weaponInfos.m_projectileInfos.POSITION = m_position;
	GameObjectPool::GetInstance()->TakeProjectileFromPool(m_weaponInfos.m_projectileInfos);
}

void LaserGun::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void LaserGun::OnStart()
{
	// Initialize projectile infos
	SProjectileData data;
	data.DIRECTION = NO_DIRECTION;
	data.COUNT_DOWN = LASER_PROJECTILE_WALL_BOUNCES_COUNT;
	data.RADIUS = LASER_PROJECTILE_RADIUS;
	data.LIFETIME = LASER_PROJECTILE_LIFETIME;
	data.DAMAGE = LASER_PROJECTILE_DAMAGE;
	data.SPEED = LASER_PROJECTILE_SPEED;
	data.COLOR = LASER_PROJECTILE_COLOR;
	data.WEAPON_TYPE = EWeaponType::LAZERGUN;
	SetProjectileInfos(data);

	m_weaponInfos.m_attackRate = LASER_PROJECTILE_RATE;

	Weapon::OnStart();

	// At every new weapon offsets the new weapon icon to the right
	m_uiOffset = s_uiOffsetRight;
	// Add the offset for the next weapon
	s_uiOffsetRight += WEAPON_ICON_OFFSET;


	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void LaserGun::Update(const float& deltatime)
{
	m_currentAttackTimer += deltatime;
	if (m_currentAttackTimer >= GetWeaponInfos().m_attackRate)
	{
		m_currentAttackTimer -= GetWeaponInfos().m_attackRate;
		Fire();
	}
}

void LaserGun::Render()
{
	// Add a small offset to the right at every new ExplosiveGun
	Vector2 position = m_position;
	position.x += m_uiOffset;

	// Add a small offsetdown above the explosive gun at the bottom of the player square
	position.y += LASER_ICON_ROW_OFFSET;
	DrawRectangleV(position, m_size, m_color);
}
