//#include <stdlib.h> 
#include <iostream>
#include <raylib.h>

#include "Projectile.h"
#include "Game.h"
#include "MathUtils.h"

unsigned short int Projectile::s_id = 0;

Projectile::Projectile(SProjectileData& projectileData, Vector2 origin, float size, float speed, float lifetime)
	: m_projectileData(projectileData)
{
	m_id = s_id++;
	m_gameObjectType = EGameObjectType::PROJECTILE;
	m_position = origin;
	m_currentLifetime = lifetime;
	m_radius = size;
	m_color = WHITE;

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
		m_xSpeed = speed * m_xSpeed;
		m_ySpeed = speed * m_ySpeed;

		return;
	}

	//If no Enemy in range, generate random direction

	// Calculate the magnitude of the speed vector : squareroot of (x*x + y*y)
	float speedMagnitude = GetMagnitude({ speed, speed });

	// Generate a random angle
	float randomRadianAngle = static_cast<float>(rand()) / RAND_MAX;
	float randomAngle = FULL_CIRCLE * randomRadianAngle;

	// Calculate new normalized speed values with the same magnitude
	m_xSpeed = speedMagnitude * cos(randomAngle);
	m_ySpeed = speedMagnitude * sin(randomAngle);

}

void Projectile::OnStart()
{
	GameObject::OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void Projectile::Update(float deltatime)
{
	m_position.x += m_xSpeed * deltatime;
	m_position.y += m_ySpeed * deltatime;
	m_currentLifetime -= GetFrameTime();
	if (m_currentLifetime < 0)
	{
		Reset();
		Game::GetInstance()->UnregisterGameObject(this);
	}
}

void Projectile::Render()
{
	DrawCircleV(m_position, m_radius, m_color);
}

void Projectile::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}