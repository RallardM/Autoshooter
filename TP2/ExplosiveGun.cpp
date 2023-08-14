#include "ExplosiveGun.h"
#include <corecrt_math.h>
#include "MathUtils.h"

float ExplosiveGun::s_uiOffsetRight = 0.0f;

void ExplosiveGun::Fire()
{
	// Initialize projectile infos
	GetProjectileInfos().RADIUS = 7.0f;
	GetProjectileInfos().LIFETIME = 0.5f;
	GetProjectileInfos().DAMAGE = 15.0f;
	GetProjectileInfos().SPEED = 50.0f;
	GetProjectileInfos().COLOR = GOLD;
	GetProjectileInfos().WEAPON_TYPE = EWeaponType::EXPLOSIVE_GUN;

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

		Projectile* projectile = new Projectile(GetProjectileInfos(), projectilePosition, projectileDirection);
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
	SetProjectileInfos(SProjectileData());

	Weapon::OnStart();

	m_uiOffset = s_uiOffsetRight;
	s_uiOffsetRight += 5.0f;

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void ExplosiveGun::Update(float deltatime)
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
