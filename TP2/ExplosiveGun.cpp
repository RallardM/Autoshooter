#include "ExplosiveGun.h"
#include "Projectile.h"

ExplosiveGun::ExplosiveGun()
	:Weapon()
{
	m_fireMode = FireMode::Mannual;
	Load();
}

ExplosiveGun::ExplosiveGun(const float& x, const float& y)
	: Weapon(x, y)
{
	m_fireMode = FireMode::Mannual;
	Load();
}

ExplosiveGun::ExplosiveGun(const float& x, const float& y, const FireMode& fireMode, const bool& isDie)
	: Weapon(x, y, fireMode ,isDie)
{
	m_fireMode = FireMode::Mannual;
	Load();
}

ExplosiveGun::~ExplosiveGun()
{}



void ExplosiveGun::OnStart()
{
	Game::GetInstance()->RegisterGameObjects(this);
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			m_projectiles[i]->OnStart();
		}
	}
}

void ExplosiveGun::Load()
{
	Vector2 projectilePosition = { 0.0f, 0.0f };
	Vector2 projectileDirection = { 0.0f, 0.0f };
	int projectilesNumber = 8;
	float teta = (2 * PI) / projectilesNumber;
	float angle = 0.0f;
	int radius = 16;

	if (m_projectiles.empty())
	{
		//Construction shape of projectile
		for (int i = 0; i < projectilesNumber; i++)
		{
			projectilePosition.x = radius * cosf(angle);
			projectilePosition.y = radius * sinf(angle);

			projectileDirection.x = projectilePosition.x;
			projectileDirection.y = projectilePosition.y;

			projectilePosition.x += m_position.x;
			projectilePosition.y += m_position.y;

			m_projectiles.emplace_back(new Projectile(projectilePosition.x, projectilePosition.y, projectileDirection.x, projectileDirection.y));

			angle += teta;
		}

	}
}

void ExplosiveGun::Reload()
{

	if (!m_projectiles.empty())
	{
		// Recharge all projectiles
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			if (m_projectiles[i]->m_isDie && m_projectiles[i]->m_lifeTime > 0.0f)
			{
				m_projectiles[i]->Reload(m_position.x, m_position.y);
			}
		}
	}
}

void ExplosiveGun::Fire()
{

	if (!m_projectiles.empty())
	{
		// Fire all projectiles
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			if (m_fireMode == FireMode::Auto)
			{
				if (m_projectiles[i]->m_isDie && m_projectiles[i]->m_lifeTime == 0.0f)
				{
					m_projectiles[i]->Fire();
				}

			}
			else if (m_fireMode == FireMode::Mannual)
			{
				if (m_projectiles[i]->m_isDie && m_projectiles[i]->m_lifeTime == 0.0f)
				{
					m_projectiles[i]->Reload(m_position.x, m_position.y);
					m_projectiles[i]->Fire();
				}
			}

		}
	}
}

void ExplosiveGun::ReloadProjectile(Projectile* projectile)
{
	// Recharge unique projectile
	projectile->Reload(m_position.x, m_position.y);
}

void ExplosiveGun::FireProjectile(Projectile* projectile)
{
	// Fire unique projectile
	projectile->Fire();
}

void ExplosiveGun::UpdatePosition(float& x, float& y)
{
	m_position.x = x;
	m_position.y = y;
}

void ExplosiveGun::Update(float deltatime)
{
	
	if (m_fireMode == FireMode::Auto)
	{
		Fire();
		Reload();
	}
	else if (m_fireMode == FireMode::Mannual)
	{
		Reload();
	}
}

void ExplosiveGun::Render()
{
	
	DrawCircle(m_position.x, m_position.y, 5.f, GOLD);
}