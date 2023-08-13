
#include "Enemy.h"
#include "Weapon.h"
#include "Game.h"
#include <iostream>
#include "ExperienceOrb.h"

unsigned short int Enemy::s_id = 0;

Enemy::Enemy()
{
	m_id = s_id++;
}

Enemy::~Enemy()
{
	// Delete health bar
	delete m_healthBar;
	m_healthBar = nullptr;
}

void Enemy::OnStart()
{
	GameObject::OnStart();

	// Initialize health bar
	Vector2 barSize = { 32.0f, 3.0f };
	Vector2 offsetFromEnemy = { 0.0f, 33.0f };
	m_healthBar = new UIElement(this, EUIElementType::REGRESS_BAR, RED, barSize, offsetFromEnemy, m_health);
	m_healthBar->OnStart();

	// Add attributes before m_isActive = true; except for spawn position
	m_isActive = true;

	Spawn();
}

void Enemy::Update(float deltatime)
{
	// Keep VerifyHealth() at top in case the enemy dies and needs to be deactivated
	Collision();
	VerifyHealth();

	TrackPlayer();
	UpdatePosition(deltatime);

	// Update health bar position
	if (m_healthBar != nullptr)
	{
		m_healthBar->FollowPosition(m_position); // TODO Make pure virtual
	}
}

void Enemy::Render()
{
	DrawRectangleV(m_position, m_enemySize, m_color);
}

void Enemy::Reset()
{
	m_enemySize = { 32.0f, 32.0f };
	m_direction = { 0.0f, 0.0f };
	Color m_color = BLUE;
	m_health = 100;

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void Enemy::Spawn()
{
	int randCorner = std::rand() % 4;
	Vector2 randPosition = { 0.0f, 0.0f };

	// Get a reference to the camera's position
	Vector2 cameraPosition = Game::GetInstance()->GetCameraPosition();
	Vector2 cameraOffset = Game::GetInstance()->GetCameraOffset();
	float cameraZoom = Game::GetInstance()->GetCameraZoom();

	// Add a random threshold to the spawn position outside the camera view
	int randMultiple = std::rand() % 10 + 1;
	const float OUTSIDE_THRESHOLD = randMultiple* m_enemySize.x; // Enemy can spawn outside the camera view by a random threshold of its own size

	switch (randCorner)
	{
	case 0:
		// Spawn left
		randPosition.x = Game::GetInstance()->GetCameraLeftLimit() - OUTSIDE_THRESHOLD;
		// Random number between Camera Top Limit and Camera Bottom Limit
		randPosition.y = (float)(std::rand() % (int)(Game::GetInstance()->GetCameraTopLimit() - Game::GetInstance()->GetCameraBottomLimit()) + Game::GetInstance()->GetCameraBottomLimit());
		m_color = ORANGE;
		break;

	case 1:
		// Spawn top
		// Random number between Camera Left Limit and Camera Right Limit
		randPosition.x = (float)(std::rand() % (int)(Game::GetInstance()->GetCameraRightLimit() - Game::GetInstance()->GetCameraLeftLimit()) + Game::GetInstance()->GetCameraLeftLimit());
		randPosition.y = Game::GetInstance()->GetCameraTopLimit() - OUTSIDE_THRESHOLD;
		m_color = GREEN;
		break;

	case 2:
		// Spawn right
		randPosition.x = Game::GetInstance()->GetCameraRightLimit() + OUTSIDE_THRESHOLD;
		// Random number between Camera Top Limit and Camera Bottom Limit
		randPosition.y = (float)(std::rand() % (int)(Game::GetInstance()->GetCameraTopLimit() - Game::GetInstance()->GetCameraBottomLimit()) + Game::GetInstance()->GetCameraBottomLimit());
		m_color = YELLOW;
		break;

	case 3:
		// Spawn bottom
		// Random number between Camera Left Limit and Camera Right Limit
		randPosition.x = (float)(std::rand() % (int)(Game::GetInstance()->GetCameraRightLimit() - Game::GetInstance()->GetCameraLeftLimit()) + Game::GetInstance()->GetCameraLeftLimit());
		randPosition.y = Game::GetInstance()->GetCameraBottomLimit() + OUTSIDE_THRESHOLD;
		m_color = PURPLE;
		break;

	default:
		break;
	}

	m_position.x = randPosition.x;
	m_position.y = randPosition.y;
}

void Enemy::UpdatePosition(float deltatime)
{
	// Update Enemy position
	m_position.x += m_direction.x * SPEED * deltatime;
	m_position.y += m_direction.y * SPEED * deltatime;
}

void Enemy::TrackPlayer()
{
	Vector2 playerPosition = Game::GetInstance()->GetPlayerPosition();
	m_direction.x = playerPosition.x - m_position.x;
	m_direction.y = playerPosition.y - m_position.y;

	float magnitude = sqrtf
	(
		(m_direction.x * m_direction.x) +
		(m_direction.y * m_direction.y)
	);

	if (magnitude > 0.0f) 
	{ 
		m_direction.x /= magnitude;
		m_direction.y /= magnitude;
	}
}

void Enemy::Collision()
{
	Rectangle enemyRect = { m_position.x, m_position.y, m_enemySize.x, m_enemySize.y };
	bool isEnemyHitByProjctile = Game::GetInstance()->AreEnemyProjectileColliding(enemyRect);

	if (isEnemyHitByProjctile)
	{
		Projectile* projectile = Game::GetInstance()->GetCollidingProjectile(enemyRect);

		if (projectile == nullptr) { return; }
		if (projectile->m_id == m_previousProjectileId) { return; }
		m_previousProjectileId = projectile->m_id;

		short int projectileDamage = (short)projectile->GetDamage();
		m_health -= projectileDamage;
	}
}

void Enemy::VerifyHealth()
{
	if (m_health <= 0)
	{
		GenerateXPOrb();

		m_healthBar->Reset();
		Game::GetInstance()->UnregisterGameObject(m_healthBar);

		Reset();
		Game::GetInstance()->UnregisterGameObject(this);
	}
}

void Enemy::GenerateXPOrb()
{
	ExperienceOrb* xpOrb = new ExperienceOrb(m_position);
	xpOrb->OnStart();
}