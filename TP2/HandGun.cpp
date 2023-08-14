#include "HandGun.h"
#include "Game.h"

float HandGun::s_uiOffsetRight = 0.0f;

void HandGun::Fire()
{
	Vector2 noDirection = { 0.0f, 0.0f };
	Projectile* projectile = new Projectile(m_weaponInfos.m_projectileInfos, m_position, noDirection);
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

	// Initialize projectile infos
	SProjectileData data;
	data.RADIUS = 5.0f;
	data.LIFETIME = 3.0f;
	data.DAMAGE = 20.0f;
	data.SPEED = 300.0f;
	data.COLOR = LIGHTGRAY;
	data.WEAPON_TYPE = EWeaponType::HAND_GUN;
	SetProjectileInfos(data);

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
	position.y += 27.0f;
	DrawRectangleV(position, m_size, m_color);
}