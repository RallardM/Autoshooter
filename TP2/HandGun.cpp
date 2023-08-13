#include "HandGun.h"
#include "Game.h"

void HandGun::Fire()
{
	Projectile* projectile = new Projectile(
		GetProjectileInfos(),
		m_position,
		GetWeaponInfos().m_projectileInfos.RADIUS,
		GetWeaponInfos().m_projectileInfos.SPEED,
		GetWeaponInfos().m_projectileInfos.LIFETIME);

	projectile->OnStart();
}

void HandGun::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void HandGun::OnStart()
{
	GameObject::OnStart();
	SetProjectileInfos(SProjectileData());

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void HandGun::Update(float deltatime)
{
	m_currentAttackTimer += deltatime;
	if (m_currentAttackTimer >= GetWeaponInfos().m_attackRate)
	{
		m_currentAttackTimer -= GetWeaponInfos().m_attackRate;
		Fire();
	}
}

void HandGun::Render()
{
	DrawRectangleV(m_position, m_size, { 255, 255, 0, 255 });
}
