#include <raylib.h>

#include "Weapon.h"
#include <iostream>

// TODO Remi : Code initial, vérifier à retirer une fois terminee
//void Weapon::OnStart()
//{
//	GameObject::OnStart();
//	m_weaponInfos.m_projectileInfos = SHandGunProjectileData();
//}
//
//void Weapon::Update()
//{
//	float frameTime = GetFrameTime();
//	m_currentAttackTimer += frameTime;
//	if (m_currentAttackTimer >= m_weaponInfos.m_attackRate)
//	{
//		m_currentAttackTimer -= m_weaponInfos.m_attackRate;
//		Fire();
//	}
//}
//
//void Weapon::Render()
//{
//	DrawRectangleV(m_position, m_size, { 255, 255, 0, 255 });
//}
//
//void Weapon::Fire()
//{
//	Projectile* projectile = new Projectile(10.0f, 10.0f, 5.0f, 
//		m_weaponInfos.m_projectileInfos.Lifetime);
//	projectile->OnStart();
//}

void Weapon::FollowPosition(Vector2 newPosition)
{
	//std::cout << "Weapon new position : " << newPosition.x << ", " << newPosition.y << std::endl;
	m_position = newPosition;
}
