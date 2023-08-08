#include "Weapon.h"
#include "Projectile.h"

Weapon::Weapon(float& x, float& y)
{
	m_position.x = x;
	m_position.y = y;
	m_isDie = false;
	
}


Weapon::~Weapon()
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			delete m_projectiles[i];
		}
	}
}


void Weapon::OnStart()
{
	Game::GetInstance()->RegisterGameObjects(this);
	
}

void Weapon::Fire()
{
	
	if (m_projectiles.empty())
	{
		CreateProjectiles();
		LaunchProjectiles();
	}
}

void Weapon::CreateProjectiles()
{
	Vector2 projectilePosition = { 0.0f, 0.0f };
	Vector2 projectileDirection = {0.0f, 0.0f};
	int projectilesNumber = 8;
	float teta = (2 * PI) / projectilesNumber;
	float angle = 0.0f;
	int radius = 64;
	
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

void Weapon::LaunchProjectiles()
{
	if (!m_projectiles.empty())
	{
		// Launch projectile
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			m_projectiles[i]->Launch();
		}

	}
}

void Weapon::ResetProjectile(Projectile* projectile)
{
	projectile->Reset(m_position.x, m_position.y);
}

void Weapon::LaunchProjectile(Projectile* projectile)
{
	projectile->Launch();
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
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			
			if (!m_projectiles[i]->m_isDie)
			{
				m_projectiles[i]->Update(deltatime);
			}
			
			else if (m_projectiles[i]->m_isDie)
			{
				m_projectiles[i]->Reset(m_position.x, m_position.y);
				m_projectiles[i]->Launch();
			}
		}
	}
}

void Weapon::Render()
{
	
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			if (!m_projectiles[i]->m_isDie)
			{
				m_projectiles[i]->Render();
			}
		}
	}
	
}