
#include "Enemy.h"
#include "Weapon.h"
#include "Game.h"
#include <iostream>
#include "ExperienceOrb.h"

Enemy::Enemy()
{
	Spawn();
	m_direction = { 0.0f, 0.0f };
	m_speed = MIN_ENEMY_SPEED;
}

Enemy::~Enemy()
{
	// TODO
}

void Enemy::OnStart()
{
	GameObject::OnStart();
}

void Enemy::Spawn()
{
	int randCorner = std::rand() % 4;
	m_speed = std::rand() % (int)(MAX_ENEMY_SPEED - MIN_ENEMY_SPEED) + MAX_ENEMY_SPEED;
	Vector2 randPosition = { 0.0f, 0.0f };

	// Get a reference to the camera's position
	Vector2 cameraPosition = Game::GetInstance()->GetCameraPosition();

	switch (randCorner)
	{
	case 0:
		// Spawn left
		randPosition.x = Game::GetInstance()->GetCameraLeftLimit() - m_enemySize.x;
		randPosition.y = cameraPosition.y;
		break;
	case 1:
		// Spawn top
		randPosition.x = cameraPosition.x;
		randPosition.y = Game::GetInstance()->GetCameraTopLimit() - m_enemySize.y;
		break;
	case 2:
		// Spawn right
		randPosition.x = Game::GetInstance()->GetCameraRightLimit() + m_enemySize.x;
		randPosition.y = cameraPosition.y;
		break;
	case 3:
		// Spawn bottom
		randPosition.x = cameraPosition.x;
		randPosition.y = Game::GetInstance()->GetCameraBottomLimit() + m_enemySize.y;
		break;
	default:
		break;
	}

	m_position.x = randPosition.x;
	m_position.y = randPosition.y;
}


void Enemy::Update()
{
	// Update Enemy position
	m_position.x += m_direction.x * m_speed;// *deltatime;
	m_position.y += m_direction.y * m_speed;// *deltatime;

	TrackPlayer();
	Collision();
	VerifyHealth();
}

void Enemy::Render()
{
	DrawRectangleV(m_position, m_enemySize, m_color);
}

void Enemy::TrackPlayer()
{
	Vector2 playerPosition = Game::GetInstance()->GetPlayerPosition();
	m_direction.x = playerPosition.x - m_position.x;
	m_direction.y = playerPosition.y - m_position.y;

	float magnitude = sqrtf(
		(m_direction.x * m_direction.x) +
		(m_direction.y * m_direction.y)
	);
	m_direction.x /= magnitude;
	m_direction.y /= magnitude;
}

void Enemy::Collision()
{
	Rectangle enemyRect = { m_position.x, m_position.y, m_enemySize.x, m_enemySize.y };
	bool isEnemyHitByProjctile = Game::GetInstance()->AreEnemyProjectileColliding(enemyRect);

	if (isEnemyHitByProjctile)
	{
		m_health -= 50;
		//TODO: Destroy projectile too
	}
}

void Enemy::VerifyHealth()
{
	if (m_health <= 0)
	{
		GenerateXPOrb();
		Game::GetInstance()->UnregisterGameObject(this);
	}
}

void Enemy::GenerateXPOrb()
{
	ExperienceOrb* xpOrb = new ExperienceOrb(m_position);
	xpOrb->OnStart();
}