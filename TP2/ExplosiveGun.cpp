#include <iostream>
#include <corecrt_math.h>

#include "ExplosiveGun.h"
#include "MathUtils.h"
#include "Globals.h"
#include "GameObjectPool.h"

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
	Vector2 projectilePosition = NO_POSITION;
	Vector2 projectileDirection = NO_DIRECTION;
	int projectilesNumber = EXPLOSIVE_PROJECTILE_NUMBER;
	float teta = FULL_CIRCLE / projectilesNumber;
	float angle = NO_ANGLE;
	int radius = EXPLOSIVE_PROJECTILE_EXPLOSION_RADIUS;

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

		GameObjectPool::GetInstance()->TakeProjectileFromPool(m_weaponInfos.m_projectileInfos);

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
	// Initialize projectile infos
	SProjectileData data;
	data.DIRECTION = NO_DIRECTION;
	data.COUNT_DOWN = NO_COUNTDOWN;
	data.RADIUS = EXPLOSIVE_PROJECTILE_RADIUS;
	data.LIFETIME = EXPLOSIVE_PROJECTILE_LIFETIME;
	data.DAMAGE = EXPLOSIVE_PROJECTILE_DAMAGE;
	data.SPEED = EXPLOSIVE_PROJECTILE_SPEED;
	data.COLOR = EXPLOSIVE_PROJECTILE_COLOR;
	data.WEAPON_TYPE = EWeaponType::EXPLOSIVEGUN;
	SetProjectileInfos(data);

	m_weaponInfos.m_attackRate = EXPLOSIVE_PROJECTILE_RATE;

	Weapon::OnStart();

	// At every new weapon offsets the new weapon icon to the right
	m_uiOffset = s_uiOffsetRight;
	// Add the offset for the next weapon
	s_uiOffsetRight += WEAPON_ICON_OFFSET;
	
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
	position.y += EXPLOSIVE_ICON_ROW_OFFSET;
	DrawRectangleV(position, m_size, m_color);
}