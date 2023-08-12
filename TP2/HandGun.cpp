#include "HandGun.h"
#include "Game.h"

void HandGun::Fire()
{
	Projectile* projectile = new Projectile(
		m_position,
		m_weaponInfos.m_projectileInfos.RADIUS,
		m_weaponInfos.m_projectileInfos.SPEED,
		m_weaponInfos.m_projectileInfos.LIFETIME);
	
	projectile->OnStart();
}

HandGun::HandGun()
{
	// TODO Remi : 
}

void HandGun::OnStart()
{
	GameObject::OnStart();
	m_weaponInfos.m_projectileInfos = SHandGunProjectileData();
}

void HandGun::Update()
{
	float frameTime = GetFrameTime();
	m_currentAttackTimer += frameTime;
	if (m_currentAttackTimer >= m_weaponInfos.m_attackRate)
	{
		m_currentAttackTimer -= m_weaponInfos.m_attackRate;
		Fire();
	}
}

void HandGun::Render()
{
	DrawRectangleV(m_position, m_size, { 255, 255, 0, 255 });
}