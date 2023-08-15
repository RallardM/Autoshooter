#include <iostream>
#include "LaserGun.h"

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
	Vector2 noDirection = { 0.0f, 0.0f };
	Projectile* projectile = new Projectile(m_weaponInfos.m_projectileInfos, m_position, noDirection);
	projectile->OnStart();
}

void LaserGun::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void LaserGun::OnStart()
{
	GameObject::OnStart();

	// Initialize projectile infos
	SProjectileData data;
	data.RADIUS = 4.0f;
	data.LIFETIME = 2.0f;
	data.DAMAGE = 100.0f;
	data.SPEED = 600.0f;
	data.COLOR = SKYBLUE;
	data.WEAPON_TYPE = EWeaponType::LAZER_GUN;
	SetProjectileInfos(data);

	Weapon::OnStart();

	m_uiOffset = s_uiOffsetRight;
	s_uiOffsetRight += UI_OFFSET_SET_RIGHT;

	m_weaponInfos.m_attackRate = 3.0f;

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void LaserGun::Update(float deltatime)
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
	position.y += LAZER_GUN_OFFSET;
	DrawRectangleV(position, m_size, m_color);
}
