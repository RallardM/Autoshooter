#include "HandGun.h"
#include "Game.h"

float HandGun::s_uiOffsetRight = 0.0f;

void HandGun::Fire()
{
	// Initialize projectile infos
	GetProjectileInfos().WEAPON_TYPE = EWeaponType::HAND_GUN;

	Vector2 noDirection = { 0.0f, 0.0f };
	Projectile* projectile = new Projectile(GetProjectileInfos(), m_position, noDirection);
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

	Weapon::OnStart();

	m_uiOffset = s_uiOffsetRight;
	s_uiOffsetRight += 5.0f;

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
	// Add a small offset to the right at every new ExplosiveGun
	Vector2 position = m_position;
	position.x += m_uiOffset;

	// Add an offset down at the bottom of the player square
	position.y += 35.0f;
	DrawRectangleV(position, m_size, m_color);
}
