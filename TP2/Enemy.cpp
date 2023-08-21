
#include <iostream>

#include "Enemy.h"
#include "Weapon.h"
#include "ExperienceOrb.h"
#include "CollisionManager.h"
#include "GameObjectPool.h"
#include "CameraManager.h"

unsigned short int Enemy::s_id = 0;

Enemy::Enemy()
{
	m_id = s_id++;
	std::cout << "Enemy constructor called. ID : " << m_id << std::endl;
}

Enemy::~Enemy()
{
	std::cout << "Enemy destructor called  ID : " << m_id << std::endl;
}

void Enemy::OnStart()
{
	// Initialize health bar
	SUIElementData* enemyHealthBarData = new SUIElementData;
	enemyHealthBarData->COLOR = RED;
	enemyHealthBarData->BAR_SIZE = ENEMY_HEALTH_BAR_SIZE;
	enemyHealthBarData->OFFSET = ENEMY_HEALTH_BAR_OFFSET;
	enemyHealthBarData->FLOAT_VALUE = m_health;
	enemyHealthBarData->FONT_SIZE = 0;
	enemyHealthBarData->UIELEMENT_TYPE = static_cast<unsigned short int>(EUIElementType::REGRESS_BAR);
	enemyHealthBarData->INT_VALUE = 0;
	enemyHealthBarData->TARGET_ID = m_entityId;
	enemyHealthBarData->HAS_SECONDARY_BAR = false;	
	GameObjectPool::GetInstance()->TakeUIElementFromPool(enemyHealthBarData);

	// Add attributes before m_isActive = true; except for spawn position
	m_isActive = true;

	Spawn();
}

void Enemy::Update(const float& deltatime)
{
	// Keep VerifyHealth() at top in case the enemy dies and needs to be deactivated
	Collision();
	VerifyHealth();

	TrackPlayer();
	UpdatePosition(deltatime);

	// Update health bar position
	if (GameObjectPool::GetInstance()->GetEnemyHealthBar(m_id) != nullptr)
	{
		GameObjectPool::GetInstance()->GetEnemyHealthBar(m_id)->FollowPosition(m_position); // TODO Make pure virtual
	}
}

void Enemy::Render()
{
	DrawRectangleV(m_position, m_enemySize, m_color);
}

void Enemy::Reset()
{
	m_enemySize = ENEMY_SIZE;
	m_direction = NO_DIRECTION;
	Color m_color = ENEMY_DEFAULT_COLOR;
	m_health = ENTITY_DEFAULT_HEALTH;

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void Enemy::Spawn()
{
	int randCorner = std::rand() % SCREEN_CORNER_COUNT;
	Vector2 randPosition = NO_POSITION;

	// Get a reference to the camera's position
	Vector2 cameraPosition = CameraManager::GetInstance()->GetCameraPosition();
	Vector2 cameraOffset = CameraManager::GetInstance()->GetCameraOffset();
	float cameraZoom = CameraManager::GetInstance()->GetCameraZoom();

	// Add a random threshold to the spawn position outside the camera view
	int randMultiple = (std::rand() % ENEMY_SPAWN_FARTHEST_THRESHOLD) + ENEMY_SPAWN_CLOSEST_THRESHOLD; // Random number between 1 and 10, 1 is the minimum of one enemy to avoid spawning the enemy on the camera view
	const float OUTSIDE_THRESHOLD = randMultiple * m_enemySize.x; // Enemy can spawn outside the camera view by a random threshold of its own size

	switch (randCorner)
	{
	case 0:
		// Spawn left
		randPosition.x = CameraManager::GetInstance()->GetCameraLeftLimit() - OUTSIDE_THRESHOLD;
		// Random number between Camera Top Limit and Camera Bottom Limit
		randPosition.y = (float)(std::rand() % (int)(CameraManager::GetInstance()->GetCameraTopLimit() - CameraManager::GetInstance()->GetCameraBottomLimit()) + CameraManager::GetInstance()->GetCameraBottomLimit());
		m_color = ORANGE;
		break;

	case 1:
		// Spawn top
		// Random number between Camera Left Limit and Camera Right Limit
		randPosition.x = (float)(std::rand() % (int)(CameraManager::GetInstance()->GetCameraRightLimit() - CameraManager::GetInstance()->GetCameraLeftLimit()) + CameraManager::GetInstance()->GetCameraLeftLimit());
		randPosition.y = CameraManager::GetInstance()->GetCameraTopLimit() - OUTSIDE_THRESHOLD;
		m_color = GREEN;
		break;

	case 2:
		// Spawn right
		randPosition.x = CameraManager::GetInstance()->GetCameraRightLimit() + OUTSIDE_THRESHOLD;
		// Random number between Camera Top Limit and Camera Bottom Limit
		randPosition.y = (float)(std::rand() % (int)(CameraManager::GetInstance()->GetCameraTopLimit() - CameraManager::GetInstance()->GetCameraBottomLimit()) + CameraManager::GetInstance()->GetCameraBottomLimit());
		m_color = YELLOW;
		break;

	case 3:
		// Spawn bottom
		// Random number between Camera Left Limit and Camera Right Limit
		randPosition.x = (float)(std::rand() % (int)(CameraManager::GetInstance()->GetCameraRightLimit() - CameraManager::GetInstance()->GetCameraLeftLimit()) + CameraManager::GetInstance()->GetCameraLeftLimit());
		randPosition.y = CameraManager::GetInstance()->GetCameraBottomLimit() + OUTSIDE_THRESHOLD;
		m_color = PURPLE;
		break;

	default:
		break;
	}

	m_position.x = randPosition.x;
	m_position.y = randPosition.y;
}

void Enemy::UpdatePosition(const float& deltatime)
{
	// Update Enemy position
	m_position.x += m_direction.x * ENEMY_SPEED * deltatime;
	m_position.y += m_direction.y * ENEMY_SPEED * deltatime;
}

void Enemy::TrackPlayer()
{
	// Get a reference to the player's position
	Vector2 playerPosition = GameObjectPool::GetInstance()->GetPlayerPosition();
	m_direction.x = playerPosition.x - m_position.x;
	m_direction.y = playerPosition.y - m_position.y;

	// Normalize direction
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
	bool isEnemyHitByProjctile = CollisionManager::GetInstance()->AreEnemyProjectileColliding(enemyRect);

	if (isEnemyHitByProjctile)
	{
		const Projectile* projectile = CollisionManager::GetInstance()->GetCollidingProjectile(enemyRect);

		if (projectile == nullptr) 
		{ 
			return; 
		}

		if (projectile->m_id == m_previousProjectileId) 
		{
			return;
		}

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

		UIElement* enemyHealthBar = GameObjectPool::GetInstance()->GetEnemyHealthBar(m_entityId);
		if(enemyHealthBar == nullptr) { return; }

		enemyHealthBar->Reset();
		Reset();
	}
}

void Enemy::GenerateXPOrb()
{
	GameObjectPool::GetInstance()->TakeExperienceOrbFromPool(m_position);
}