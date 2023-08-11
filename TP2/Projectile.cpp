//#include <stdlib.h> 
#include <iostream>
#include <raylib.h>

#include "Projectile.h"
#include "Game.h"
#include "MathUtils.h"

unsigned short int Projectile::s_id = 0;

//Projectile::Projectile(Vector2 origin, float xSpeed, float ySpeed, float size, float lifetime)
Projectile::Projectile(Vector2 origin, float size, float speed, float lifetime)
{
	m_id = s_id++;
	m_gameObjectType = EGameObjectType::PROJECTILE;
	m_position = origin;
	m_currentLifetime = lifetime;
	m_radius = size;
	m_color = WHITE;

	float diameter = m_radius * 2;
	// BoxCollider
	//m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	m_boxCollider = new BoxCollider(m_position.x + m_radius, m_position.y + m_radius, diameter, diameter);

	GameObject* closestGameObject = Game::GetClosestGameObject(m_position, EGameObjectType::ENEMY);
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

Projectile::~Projectile()
{
	delete m_boxCollider;
}

void Projectile::OnStart()
{
	GameObject::OnStart();
	//m_position.x = (float)GetScreenWidth() / 2.0f; // TODO
	//m_position.y = (float)GetScreenHeight() / 2.0f;// TODO
}

void Projectile::Update()
{
	m_position.x += m_xSpeed;
	m_position.y += m_ySpeed;
	m_currentLifetime -= GetFrameTime();
	if (m_currentLifetime < 0)
	{
		Game::GetInstance()->UnregisterGameObject(this);
	}
}

void Projectile::Render()
{
	DrawCircleV(m_position, m_radius, m_color);
	// TODO Remi : Vérifier code ajouté par Maurice:
	//DrawRectangle(m_boxCollider->m_left, m_boxCollider->m_top, m_width, m_height, m_color);
}

//Enemy* Projectile::FindClosestEnemyToPlayer()
//{
//	Enemy* closestEnemy = nullptr;
//	float minDistance = std::numeric_limits<float>::max(); // Start with a large distance
//
//	//for (Enemy* enemy : Game::GetEnemies())
//	for (GameObject* gameObject : Game::GetGameObjects())
//	{
//		if (gameObject->GetGameObjectType() != EGameObjectType::ENEMY)
//		{
//			continue;
//		}
//
//		// Calculate the distance between player and enemy
//		float distance = Vector2Distance(gameObject->GetPosition(), Game::GetPlayerPosition());
//
//		// Check if the enemy is within camera bounds
//		if (Game::IsWithinCameraBounds(gameObject->GetPosition()))
//		{
//			// Update the closest enemy if the current enemy is closer
//			if (distance < minDistance)
//			{
//				minDistance = distance;
//				closestEnemy = gameObject;
//			}
//		}
//	}
//
//	return closestEnemy;
//}
