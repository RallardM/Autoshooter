#include "LaserGun.h"

float LaserGun::s_uiOffsetRight = 0.0f;

void LaserGun::Fire()
{
	// Initialize projectile infos
	GetProjectileInfos().RADIUS = 4.0f;
	GetProjectileInfos().LIFETIME = 2.0f;
	GetProjectileInfos().DAMAGE = 100.0f;
	GetProjectileInfos().SPEED = 600.0f;
	GetProjectileInfos().COLOR = SKYBLUE;
	GetProjectileInfos().WEAPON_TYPE = EWeaponType::LAZER_GUN;

	Vector2 noDirection = { 0.0f, 0.0f };
	Projectile* projectile = new Projectile(GetProjectileInfos(), m_position, noDirection);
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
	SetProjectileInfos(SProjectileData());

	Weapon::OnStart();

	m_uiOffset = s_uiOffsetRight;
	s_uiOffsetRight += 5.0f;

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
	position.y += 25.0f;
	DrawRectangleV(position, m_size, m_color);
}
