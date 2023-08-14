//#include <stdlib.h> 
#include <iostream>
#include <raylib.h>

#include "Projectile.h"
#include "Game.h"
#include "MathUtils.h"

unsigned short int Projectile::s_id = 0;

Projectile::Projectile(SProjectileData& projectileData, Vector2& origin, Vector2& direction)
	: m_projectileData(projectileData)
{
	m_id = s_id++;
	m_position = origin;
	switch (projectileData.WEAPON_TYPE)
	{
	case EWeaponType::HAND_GUN:
		SetHandGunProjectileData(projectileData);
		break;

	case EWeaponType::EXPLOSIVE_GUN:
		SetExplosiveGunProjectileValues(projectileData, direction);
		break;

	case EWeaponType::LAZER_GUN:
		SetLaserGunProjectileValues(projectileData);
		break;

	case EWeaponType::COUNT:
	default:
		std::cout << "Projectile::Projectile() : Error : Invalid weapon type" << std::endl;
		break;
	}
}

void Projectile::OnStart()
{
	GameObject::OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void Projectile::Update(float deltatime)
{
	// Lazer reflects on the screen borders
	if (m_projectileData.WEAPON_TYPE == EWeaponType::LAZER_GUN && m_laserBounces > 0)
	{
		if (m_position.x < CameraManager::GetInstance()->GetCameraLeftLimit() || m_position.x > CameraManager::GetInstance()->GetCameraRightLimit())
		{
			m_xSpeed = -m_xSpeed;
			m_laserBounces--;
		}
		if (m_position.y < CameraManager::GetInstance()->GetCameraTopLimit() || m_position.y > CameraManager::GetInstance()->GetCameraBottomLimit())
		{
			m_ySpeed = -m_ySpeed;
			m_laserBounces--;
		}
	}

	m_position.x += m_xSpeed * deltatime;
	m_position.y += m_ySpeed * deltatime;
	m_currentLifetime -= deltatime;
	if (m_currentLifetime < 0)
	{
		Reset();
		Game::GetInstance()->UnregisterGameObject(this);
	}
}

void Projectile::Render()
{
	switch (m_projectileData.WEAPON_TYPE)
	{
		case EWeaponType::HAND_GUN:
			DrawCircleV(m_position, m_radius, m_color);
			break;

		case EWeaponType::EXPLOSIVE_GUN:
			DrawPoly(m_position, 3, m_radius, 0.0f, m_color);
			break;

		case EWeaponType::LAZER_GUN:
			DrawLineEx(m_position, { m_position.x + m_xSpeed * EIGHTH, m_position.y + m_ySpeed * EIGHTH }, m_radius, m_color);
			break;

		case EWeaponType::COUNT:
			default:
			std::cout << "Projectile::Render() : Error : Invalid weapon type" << std::endl;
			break;
	}
}

void Projectile::SetHandGunProjectileData(SProjectileData& projectileData)
{
	m_currentLifetime = projectileData.LIFETIME;
	m_radius = projectileData.RADIUS;
	m_color = projectileData.COLOR;

	float diameter = m_radius * 2;

	GameObject* closestGameObject = Game::GetInstance()->GetClosestGameObject(m_position, EGameObjectType::ENEMY);
	if (closestGameObject != nullptr)
	{
		Enemy* closestEnemy = dynamic_cast<Enemy*>(closestGameObject);

		// Calculate the direction of the projectile towards the closest enemy
		float xDirection = closestEnemy->GetPosition().x - m_position.x;
		float yDirection = closestEnemy->GetPosition().y - m_position.y;

		// Normalize the direction of the projectile
		float directionMagnitude = GetMagnitude({ xDirection, yDirection });
		m_xSpeed = xDirection / directionMagnitude;
		m_ySpeed = yDirection / directionMagnitude;

		// Calculate new normalized speed values with the same magnitude
		m_xSpeed = projectileData.SPEED * m_xSpeed;
		m_ySpeed = projectileData.SPEED * m_ySpeed;

		return;
	}

	//If no Enemy in range, generate random direction

	// Calculate the magnitude of the speed vector : squareroot of (x*x + y*y)
	float speedMagnitude = GetMagnitude({ projectileData.SPEED, projectileData.SPEED });

	// Generate a random angle
	float randomRadianAngle = static_cast<float>(rand()) / RAND_MAX;
	float randomAngle = FULL_CIRCLE * randomRadianAngle;

	// Calculate new normalized speed values with the same magnitude
	m_xSpeed = speedMagnitude * cos(randomAngle);
	m_ySpeed = speedMagnitude * sin(randomAngle);
}

void Projectile::SetExplosiveGunProjectileValues(SProjectileData& projectileData, Vector2& direction)
{
	m_currentLifetime = projectileData.LIFETIME;
	m_radius = projectileData.RADIUS;
	m_color = projectileData.COLOR;

	m_xSpeed += direction.x * projectileData.SPEED;
	m_ySpeed += direction.y * projectileData.SPEED;

}

void Projectile::SetLaserGunProjectileValues(SProjectileData& projectileData)
{
	m_currentLifetime = projectileData.LIFETIME;
	m_radius = projectileData.RADIUS;
	m_color = projectileData.COLOR;

	// Calculate the magnitude of the speed vector : squareroot of (x*x + y*y)
	float speedMagnitude = GetMagnitude({ projectileData.SPEED, projectileData.SPEED });

	// Generate a random angle
	float randomRadianAngle = static_cast<float>(rand()) / RAND_MAX;
	float randomAngle = FULL_CIRCLE * randomRadianAngle;

	// Calculate new normalized speed values with the same magnitude
	m_xSpeed = speedMagnitude * cos(randomAngle);
	m_ySpeed = speedMagnitude * sin(randomAngle);
}

void Projectile::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}