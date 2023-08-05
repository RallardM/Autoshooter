#include "Weapon.h"

Weapon::Weapon(float& x, float& y)
{
	m_position.x = x;
	m_position.y = y;

	m_shapeCornersNumber = 8;
	m_radius = 64.0f;
	m_projectilePosition = { 0.0f, 0.0f };
	m_teta = (2 * PI) / m_shapeCornersNumber;
	m_angle = 0.0f;

	
}


Weapon::~Weapon()
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_shapeCornersNumber; i++)
		{
			delete m_projectiles[i];
		}
	}
}


void Weapon::OnStart()
{

}

void Weapon::Fire()
{
	if (m_projectiles.empty())
	{
		CreateProjectiles();
		LaunchProjectiles();
	}
	else
	{
		LaunchProjectiles();
	}
}

void Weapon::CreateProjectiles()
{
	Vector2 projectileDirection = {0.0f, 0.0f};
	
	if (m_projectiles.empty())
	{
		//Construction shape of projectile
		for (int i = 0; i < m_shapeCornersNumber; i++)
		{
			m_projectilePosition.x = m_radius * cosf(m_angle);
			m_projectilePosition.y = m_radius * sinf(m_angle);
		
			projectileDirection.x = m_projectilePosition.x;
			projectileDirection.y = m_projectilePosition.y;

			m_projectilePosition.x += m_position.x;
			m_projectilePosition.y += m_position.y;

			m_projectiles.emplace_back(new Projectile(m_projectilePosition.x, m_projectilePosition.y, projectileDirection.x, projectileDirection.y));

			m_angle += m_teta;
		}

	}
}

void Weapon::LaunchProjectiles()
{
	if (!m_projectiles.empty())
	{
		// Launch projectile
		for (int i = 0; i < m_shapeCornersNumber; i++)
		{
			if (!m_projectiles[i]->m_isDie && m_projectiles[i]->m_lifeTime == 0.0f)
			{
				m_projectiles[i]->Launch();

			}
			else if (m_projectiles[i]->m_isDie && m_projectiles[i]->m_lifeTime == 0.0f)
			{
				m_projectiles[i]->m_isDie = false;
				m_projectiles[i]->Launch();
			}

		}

	}
}

void Weapon::ResetProjectile(Projectile* projectile)
{
	projectile->Reset(m_position.x, m_position.y);
}

void Weapon::LaunchProjectile(Projectile* projectile)
{

	if (projectile->m_isDie && projectile->m_lifeTime == 0.0f)
	{
		projectile->m_isDie = false;
		projectile->Launch();
	}
}


void Weapon::UpdatePosition(float& x, float& y)
{
	m_position.x = x;
	m_position.y = y;
}

void Weapon::Update(float deltatime)
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_shapeCornersNumber; i++)
		{
			if (!m_projectiles[i]->m_isDie)
			{
				m_projectiles[i]->Update(deltatime);
			}
			else
			{
				m_projectiles[i]->Reset(m_position.x, m_position.y);
			}
		}
	}
}

void Weapon::Render()
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_shapeCornersNumber; i++)
		{
			if (!m_projectiles[i]->m_isDie)
			{
				m_projectiles[i]->Render();
			}
		}
	}
}