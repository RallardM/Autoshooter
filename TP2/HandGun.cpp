#include <iostream>

#include "HandGun.h"
#include "Game.h"

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
	//m_weaponInfos.m_projectileInfos.POSITION = m_position;
	Projectile* projectile = new Projectile(m_weaponInfos.m_projectileInfos, m_position);
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
	//data.POSITION = { 0.0f, 0.0f };
	data.DIRECTION = { 0.0f, 0.0f };
	data.RADIUS = 5.0f;
	data.LIFETIME = 2.0f;
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

void HandGun::Update(float& deltatime)
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