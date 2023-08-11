
#include "Enemy.h"
#include "Weapon.h"
#include "Game.h"
#include <iostream>
#include "ExperienceOrb.h"

Enemy::Enemy()
//: GameObject()
{
	//m_gameObjectType = EGameObjectType::ENEMY;
	// Position
	Spawn();
	m_direction = { 0.0f, 0.0f };
	m_speed = MIN_ENEMY_SPEED;


	// Dimension
	//m_width = ENEMY_WIDTH;
	//m_height = ENEMY_HEIGHT;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, ENEMY_WIDTH, ENEMY_HEIGHT);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}

//Enemy::Enemy(const float& x, const float& y, const bool& isDie)
////: GameObject(x, y, isDie)
//{
//	// Position
//	Spawn();
//	m_direction = { 0.0f, 0.0f };
//	m_speed = MIN_ENEMY_SPEED;
//
//	// Dimension
//	m_width = ENEMY_WIDTH;
//	m_height = ENEMY_HEIGHT;
//
//	// BoxCollider
//	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
//	// OldBoxCollider
//	m_oldBoxCollider = m_boxCollider;
//
//	m_isCollide = false;
//
//	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
//}
//
//Enemy::Enemy(const float& x, const float& y, const int& width, const int& height, const bool& isDie)
////: GameObject(x, y, isDie)
//{
//	// Position
//	Spawn();
//	m_direction = { 0.0f, 0.0f };
//	m_speed = MIN_ENEMY_SPEED;
//
//	// Dimension
//	m_width = ENEMY_WIDTH;
//	m_height = ENEMY_HEIGHT;
//
//	// BoxCollider
//	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
//	// OldBoxCollider
//	m_oldBoxCollider = m_boxCollider;
//
//	m_isCollide = false;
//
//	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
//}


Enemy::~Enemy()
{}

void Enemy::OnStart()
{
	GameObject::OnStart();
	//Game::GetInstance()->RegisterGameObject(this);
	//if (!m_weapons.empty())
	//{
	//	for (int i = 0; i < m_weapons.size(); ++i)
	//	{
	//		m_weapons[i]->OnStart();
	//	}
	//}
}


void Enemy::Spawn()
{
	int randCorner = std::rand() % 4;
	m_speed = std::rand() % (int)(MAX_ENEMY_SPEED - MIN_ENEMY_SPEED) + MAX_ENEMY_SPEED;
	Vector2 randPosition = { 0.0f, 0.0f };

	// Get a reference to the camera's position
	Vector2 cameraPosition = Game::GetCameraPosition();

	switch (randCorner)
	{
	case 0:
		// Spawn left
		randPosition.x = Game::GetCameraLeftLimit() - ENEMY_WIDTH;
		randPosition.y = cameraPosition.y;
		break;
	case 1:
		// Spawn top
		randPosition.x = cameraPosition.x;
		randPosition.y = Game::GetCameraTopLimit() - ENEMY_HEIGHT;
		break;
	case 2:
		// Spawn right
		randPosition.x = Game::GetCameraRightLimit() + ENEMY_WIDTH;
		randPosition.y = cameraPosition.y;
		break;
	case 3:
		// Spawn bottom
		randPosition.x = cameraPosition.x;
		randPosition.y = Game::GetCameraBottomLimit() + ENEMY_HEIGHT;
		break;
	default:
		break;
	}

	//switch (randCorner)
	//{
	//case 0:
	//	// Spawn left
	//	randPosition.y = static_cast<float>(std::rand() % static_cast<int>(Game::GetCameraLeftLimit()));
	//	randPosition.x = 0;
	//	break;
	//case 1:
	//	// Spawn top
	//	randPosition.y = 0;
	//	randPosition.x = static_cast<float>(std::rand() % static_cast<int>(Game::GetCameraTopLimit()));
	//	break;
	//case 2:
	//	// Spaw right
	//	randPosition.y = static_cast<float>(std::rand() % static_cast<int>(Game::GetCameraRightLimit()));
	//	randPosition.x = Game::GetCameraWidth();
	//	break;
	//case 3:
	//	// Spaw bottom
	//	randPosition.y = Game::GetCameraHeight();
	//	randPosition.x = static_cast<float>(std::rand() % static_cast<int>(Game::GetCameraBottomLimit()));
	//	break;
	//default:
	//	break;
	//}

	m_position.x = randPosition.x;
	m_position.y = randPosition.y;
}

//void Enemy::TrackPlayer(float& x, float& y)
//{
//	m_direction.x = x - m_position.x;
//	m_direction.y = y - m_position.y;
//
//	float magnitude = sqrtf(
//		(m_direction.x * m_direction.x) +
//		(m_direction.y * m_direction.y)
//	);
//	m_direction.x /= magnitude;
//	m_direction.y /= magnitude;
//}

void Enemy::Update()
{
	// Update OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	// Update Enemy position
	m_position.x += m_direction.x * m_speed;// *deltatime;

	// Update body
	m_boxCollider.Update(m_position.x, m_position.y);


	// Collision Horizontal

	// Update Enemy position
	m_position.y += m_direction.y * m_speed;// *deltatime;

	// Update rect
	m_boxCollider.Update(m_position.x, m_position.y);

	// Collision Vertical

	//Set weapon position to follow player position
	//if (!m_weapons.empty())
	//{
	//	for (int i = 0; i < m_weapons.size(); ++i)
	//	{
	//		m_weapons[i]->UpdatePosition(m_position.x, m_position.y);
	//		//m_weapons[i]->Update(deltatime);
	//	}
	//}

	TrackPlayer();
	Collision();
	VerifyHealth();
}

void Enemy::Render()
{
	/*
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			(*it)->Render();
		}
	}
	*/
	DrawRectangle((int)m_boxCollider.m_left, (int)m_boxCollider.m_top, (int)ENEMY_WIDTH, (int)ENEMY_HEIGHT, m_color);
}

void Enemy::TrackPlayer()
{
	Vector2 playerPosition = Game::GetPlayerPosition();
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
	Rectangle enemyRect = { m_position.x, m_position.y, ENEMY_WIDTH, ENEMY_HEIGHT };
	bool isEnemyHitByProjctile = Game::AreEnemyProjectileColliding(enemyRect);

	if (isEnemyHitByProjctile)
	{
		m_health -= 50;
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
