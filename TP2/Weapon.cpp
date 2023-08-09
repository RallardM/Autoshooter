#include <raylib.h>

#include "Weapon.h"

void Weapon::OnStart()
{
	GameObject::OnStart();
	m_weaponInfos.m_projectileInfos = SProjectileData();
}

void Weapon::Update()
{
	float frameTime = GetFrameTime();
	m_currentAttackTimer += frameTime;
	if (m_currentAttackTimer >= m_weaponInfos.m_attackRate)
	{
		m_currentAttackTimer -= m_weaponInfos.m_attackRate;
		Fire();
	}
}

void Weapon::Render()
{
	// TODO
}

void Weapon::Fire()
{
	Projectile* projectile = new Projectile(10.0f, 10.0f, 5.0f, 
		m_weaponInfos.m_projectileInfos.Lifetime);
	projectile->OnStart();
}