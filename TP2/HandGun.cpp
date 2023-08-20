#include <iostream>

#include "HandGun.h"
#include "Game.h"
#include "Globals.h"

float HandGun::s_uiOffsetRight = 0.0f;

unsigned short int HandGun::s_id = 0;


HandGun::HandGun()
{
	m_id = s_id++;
	std::cout << "HandGun constructor called. ID : " << m_id << std::endl;
}

HandGun::~HandGun()
{
	std::cout << "HandGun destructor called. ID : " << m_id << std::endl;
}

void HandGun::Fire()
{
	m_weaponInfos.m_projectileInfos.POSITION = m_position;
	Projectile* projectile = new Projectile(m_weaponInfos.m_projectileInfos);
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
	data.DIRECTION = NO_DIRECTION;
	data.COUNT_DOWN = NO_COUNTDOWN;
	data.RADIUS = HANDGUN_PROJECTILE_RADIUS;
	data.LIFETIME = HANDGUN_PROJECTILE_LIFETIME;
	data.DAMAGE = HANDGUN_PROJECTILE_DAMAGE;
	data.SPEED = HANDGUN_PROJECTILE_SPEED;
	data.COLOR = HANDGUN_PROJECTILE_COLOR;
	data.WEAPON_TYPE = EWeaponType::HAND_GUN;
	SetProjectileInfos(data);

	m_weaponInfos.m_attackRate = HANDGUN_PROJECTILE_RATE;

	Weapon::OnStart();

	// At every new weapon offsets the new weapon icon to the right
	m_uiOffset = s_uiOffsetRight;
	// Add the offset for the next weapon
	s_uiOffsetRight += WEAPON_ICON_OFFSET;

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void HandGun::Update(const float& deltatime)
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
	position.y += HANDGUN_ICON_ROW_OFFSET;
	DrawRectangleV(position, m_size, m_color);
}