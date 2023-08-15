#include "ExplosiveGun.h"
#include <corecrt_math.h>
#include "MathUtils.h"

float ExplosiveGun::s_uiOffsetRight = 0.0f;

void ExplosiveGun::Fire()
{
	// Initialize projectile infos
	GetProjectileInfos().RADIUS = E_PROJECTILE_RADIUS;
	GetProjectileInfos().LIFETIME = E_PROJECTILE_LIFETIME;
	GetProjectileInfos().DAMAGE = E_PROJECTILE_DAMAGE;
	GetProjectileInfos().SPEED = E_PROJECTILE_SPEED;
	GetProjectileInfos().COLOR = E_PROJECTILE_COLOR;
	GetProjectileInfos().WEAPON_TYPE = EWeaponType::EXPLOSIVE_GUN;

	// Initialize projectile position and direction
	Vector2 projectilePosition = { 0.0f, 0.0f };
	Vector2 projectileDirection = { 0.0f, 0.0f };
	int projectilesNumber = E_PROJECTILE_NUMBER;
	float teta = FULL_CIRCLE / projectilesNumber;
	float angle = 0.0f;
	int radius = E_PROJECTILE_RADIUS;

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
	s_uiOffsetRight += UI_OFFSET_SET_RIGHT;

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
	position.y += E_EXPLOSIVEGUN_OFFSET;
	DrawRectangleV(position, m_size, m_color);
}
