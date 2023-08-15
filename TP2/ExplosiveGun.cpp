#include <iostream>
#include <corecrt_math.h>

#include "ExplosiveGun.h"
#include "MathUtils.h"

float ExplosiveGun::s_uiOffsetRight = 0.0f;

unsigned short int ExplosiveGun::s_id = 0;

ExplosiveGun::ExplosiveGun()
{
	m_id = s_id++;
	std::cout <<"ExplosiveGun constructor called. ID = " << m_id << std::endl;
}

ExplosiveGun::~ExplosiveGun()
{
	std::cout << "ExplosiveGun destructor called. ID = " << m_id << std::endl;
}

void ExplosiveGun::Fire()
{
	// Initialize projectile position and direction
	Vector2 projectilePosition = { 0.0f, 0.0f };
	Vector2 projectileDirection = { 0.0f, 0.0f };
	int projectilesNumber = 8;
	float teta = FULL_CIRCLE / projectilesNumber;
	float angle = 0.0f;
	int radius = 16;

	for (int i = 0; i < projectilesNumber; i++)
	{
		projectilePosition.x = radius * cosf(angle);
		projectilePosition.y = radius * sinf(angle);

		projectileDirection.x = projectilePosition.x;
		projectileDirection.y = projectilePosition.y;

		projectilePosition.x += m_position.x;
		projectilePosition.y += m_position.y;

		m_weaponInfos.m_projectileInfos.DIRECTION = projectileDirection;
		m_weaponInfos.m_projectileInfos.POSITION = projectilePosition;
		Projectile* projectile = new Projectile(m_weaponInfos.m_projectileInfos);
		projectile->OnStart();
		angle += teta;
	}
}

void ExplosiveGun::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void ExplosiveGun::OnStart()
{
	GameObject::OnStart();

	// Initialize projectile infos
	SProjectileData data;
	data.DIRECTION = { 0.0f, 0.0f };
	data.COUNT_DOWN = 0;
	data.RADIUS = 7.0f;
	data.LIFETIME = 0.5f;
	data.DAMAGE = 40.0f;
	data.SPEED = 50.0f;
	data.COLOR = GOLD;
	data.WEAPON_TYPE = EWeaponType::EXPLOSIVE_GUN;
	SetProjectileInfos(data);

	Weapon::OnStart();

	m_uiOffset = s_uiOffsetRight;
	s_uiOffsetRight += 5.0f;

	m_weaponInfos.m_attackRate = 2.0f;

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void ExplosiveGun::Update(const float& deltatime)
{
	m_currentAttackTimer += deltatime;
	if (m_currentAttackTimer >= GetWeaponInfos().m_attackRate)
	{
		m_currentAttackTimer -= GetWeaponInfos().m_attackRate;
		Fire();
	}
}

void ExplosiveGun::Render()
{
	// Add a small offset to the right at every new ExplosiveGun
	Vector2 position = m_position;
	position.x += m_uiOffset;
	
	// Add a small offset down above the handgun at the bottom of the player square
	position.y += 22.0f;
	DrawRectangleV(position, m_size, m_color);
}
