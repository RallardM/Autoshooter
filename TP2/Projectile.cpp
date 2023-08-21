#include <iostream>
#include <raylib.h>

#include "Projectile.h"
#include "MathUtils.h"
#include "GameObjectPool.h"
#include "CameraManager.h"

unsigned short int Projectile::s_id = 0;


Projectile::Projectile(SProjectileData* projectileData) : m_radius(projectileData->RADIUS), m_currentLifetime(projectileData->LIFETIME), m_projectileData(projectileData)
{
	m_id = s_id++;

	std::cout << "Projectile default constructor called. ID = " << m_id << std::endl;
}

Projectile::~Projectile()
{
	std::cout << "Projectile destructor called. ID = " << m_id << std::endl;
}

void Projectile::OnStart()
{
	m_position = m_projectileData->POSITION;

	switch (m_projectileData->WEAPON_TYPE)
	{
	case EWeaponType::HANDGUN:
		SetHandGunProjectileData();
		break;

	case EWeaponType::EXPLOSIVEGUN:
		SetExplosiveGunProjectileValues();
		break;

	case EWeaponType::LAZERGUN:
		SetLaserGunProjectileValues();
		break;

	case EWeaponType::COUNT:
	default:
		std::cout << "Projectile::Projectile() : Error : Invalid weapon type" << std::endl;
		break;
	}

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void Projectile::Update(const float& deltatime)
{
	// Lazer reflects on the screen borders, COUNT_DOWN is the number of times the lazer can reflect on the screen borders
	if (m_projectileData->WEAPON_TYPE == EWeaponType::LAZERGUN && m_projectileData->COUNT_DOWN > 0)
	{
		if (m_position.x < CameraManager::GetInstance()->GetCameraLeftLimit() || m_position.x > CameraManager::GetInstance()->GetCameraRightLimit())
		{
			m_xSpeed = -m_xSpeed;
			m_projectileData->COUNT_DOWN--;
		}
		if (m_position.y < CameraManager::GetInstance()->GetCameraTopLimit() || m_position.y > CameraManager::GetInstance()->GetCameraBottomLimit())
		{
			m_ySpeed = -m_ySpeed;
			m_projectileData->COUNT_DOWN--;
		}
	}

	m_position.x += m_xSpeed * deltatime;
	m_position.y += m_ySpeed * deltatime;

	m_currentLifetime -= deltatime;
	if (m_currentLifetime < 0 && m_isActive)
	{
		Reset();
	}
}

void Projectile::Render()
{
	switch (m_projectileData->WEAPON_TYPE)
	{
	case EWeaponType::HANDGUN:
		DrawCircleV(m_position, m_radius, m_projectileData->COLOR);
		break;

	case EWeaponType::EXPLOSIVEGUN:
		DrawPoly(m_position, EXPLOSIVE_PROJECTILE_EDGE_NUMBER, m_radius, 0.0f, m_projectileData->COLOR);
		break;

	case EWeaponType::LAZERGUN:
		DrawLineEx(m_position, { m_position.x + m_xSpeed * EIGHTH, m_position.y + m_ySpeed * EIGHTH }, m_radius, m_projectileData->COLOR);
		break;

	case EWeaponType::COUNT:
	default:
		std::cout << "Projectile::Render() : Error : Invalid weapon type" << std::endl;
		break;
	}
}

const void Projectile::SetHandGunProjectileData()
{
	m_currentLifetime = m_projectileData->LIFETIME;

	const Enemy* closestEnemy = GameObjectPool::GetInstance()->GetClosestEnemy(m_position);
	if (closestEnemy != nullptr)
	{
		// Calculate the direction of the projectile towards the closest enemy
		float xDirection = (closestEnemy->GetPosition().x + ENEMY_SIZE.x * HALF) - m_position.x;
		float yDirection = (closestEnemy->GetPosition().y + ENEMY_SIZE.y * HALF) - m_position.y;

		// Normalize the direction of the projectile
		Vector2 direction = { xDirection, yDirection };
		float directionMagnitude = GetMagnitude(direction);
		m_xSpeed = xDirection / directionMagnitude;
		m_ySpeed = yDirection / directionMagnitude;

		// Calculate new normalized speed values with the same magnitude
		m_xSpeed = m_projectileData->SPEED * m_xSpeed;
		m_ySpeed = m_projectileData->SPEED * m_ySpeed;

		return;
	}

	// If no Enemy in range, generate random direction
	SendInRandomDirections();
}

const void Projectile::SetExplosiveGunProjectileValues()
{
	m_currentLifetime = m_projectileData->LIFETIME;

	m_xSpeed += m_projectileData->DIRECTION.x * m_projectileData->SPEED;
	m_ySpeed += m_projectileData->DIRECTION.y * m_projectileData->SPEED;
}

const void Projectile::SetLaserGunProjectileValues()
{
	m_currentLifetime = m_projectileData->LIFETIME;
	SendInRandomDirections();
}

const void Projectile::SendInRandomDirections()
{
	// Calculate the magnitude of the speed vector : squareroot of (x*x + y*y)
	Vector2 speedVector = { m_projectileData->SPEED, m_projectileData->SPEED };
	float speedMagnitude = GetMagnitude(speedVector);

	// Generate a random angle
	float randomRadianAngle = static_cast<float>(rand()) / RAND_MAX;
	float randomAngle = FULL_CIRCLE * randomRadianAngle;

	// Calculate new normalized speed values with the same magnitude
	m_xSpeed = speedMagnitude * cos(randomAngle);
	m_ySpeed = speedMagnitude * sin(randomAngle);
}

void Projectile::Reset()
{
	if (m_projectileData == nullptr)
	{
		std::cout << "Projectile::Reset() : Error : m_projectileData is nullptr" << std::endl;
		return;
	}

	delete m_projectileData;
	m_projectileData = nullptr;

	//m_projectileData->COLOR = BLANK;
	//m_projectileData->WEAPON_TYPE = EWeaponType::COUNT;
	//m_projectileData->POSITION = { 0.0f, 0.0f };
	//m_projectileData->DIRECTION = { 0.0f, 0.0f };
	//m_projectileData->SPEED = 0.0f;
	//m_projectileData->LIFETIME = 0.0f;
	//m_projectileData->COUNT_DOWN = 0;
	//m_position = { 0.0f, 0.0f };

	// Reset everything before m_isActive = false;
	m_isActive = false;
}