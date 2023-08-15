#include <iostream>

#include "CollisionManager.h"
#include "Game.h"

CollisionManager* CollisionManager::_Instance = nullptr;

CollisionManager::CollisionManager()
{
	std::cout << "CollisionManager constructor called." << std::endl;
}

CollisionManager::~CollisionManager()
{
	std::cout << "CollisionManager destructor called" << std::endl;
}

CollisionManager* CollisionManager::GetInstance()
{
    if (_Instance == nullptr)
    {
        _Instance = new CollisionManager();
    }
    return _Instance;
}

bool CollisionManager::AreEnemyProjectileColliding(Rectangle enemy)
{
	for (GameObject* gameObject : Game::GetInstance()->GetGameObjects())
	{
		if (gameObject == nullptr) { continue; }

		//if (Game::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::PROJECTILE)
		if (gameObject->GetGameObjectType() == EGameObjectType::PROJECTILE)
		{
			Projectile* projectile = dynamic_cast<Projectile*>(gameObject);
			Vector2 projectilePosition = projectile->GetPosition();
			float projectileRadius = projectile->GetRadius();

			bool IsEnemyHitByProjectile = CheckCollisionCircleRec(projectilePosition, projectileRadius, enemy);
			if (IsEnemyHitByProjectile)
			{
				return true;
			}
		}
	}
	return false;
}

Projectile* CollisionManager::GetCollidingProjectile(Rectangle enemy)
{
	for (GameObject* gameObject : Game::GetInstance()->GetGameObjects())
	{
		if (Game::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::PROJECTILE)
		{
			Projectile* projectile = dynamic_cast<Projectile*>(gameObject);
			Vector2 projectilePosition = projectile->GetPosition();
			float projectileRadius = projectile->GetRadius();

			bool IsEnemyHitByProjectile = CheckCollisionCircleRec(projectilePosition, projectileRadius, enemy);
			if (IsEnemyHitByProjectile)
			{
				return projectile;
			}
		}
	}
	return nullptr;
}

bool CollisionManager::AreOrbPlayerColliding(Vector2 orbPosition, float orbradius)
{
	bool isPlayerTouchingOrb = CheckCollisionCircleRec(orbPosition, orbradius, Game::GetInstance()->GetPlayer()->GetRect());
	if (isPlayerTouchingOrb)
	{
		return true;
	}
	return false;
}

bool CollisionManager::ArePlayerEnemyColliding(Rectangle player)
{
	for (GameObject* gameObject : Game::GetInstance()->GetGameObjects())
	{
		if (gameObject == nullptr) { continue; }

		if (Game::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::ENEMY)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(gameObject);
			Vector2 enemyPosition = enemy->GetPosition();
			Rectangle enemyRect = enemy->GetRect();

			bool IsEnemyHitByProjectile = CheckCollisionRecs(player, enemyRect);
			if (IsEnemyHitByProjectile)
			{
				return true;
			}
		}
	}
	return false;
}

Enemy* CollisionManager::GetCollidingEnemy(Rectangle player)
{
	for (GameObject* gameObject : Game::GetInstance()->GetGameObjects())
	{
		if (Game::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::ENEMY)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(gameObject);
			Vector2 enemyPosition = enemy->GetPosition();
			Rectangle enemyRect = enemy->GetRect();

			bool IsEnemyHitByProjectile = CheckCollisionRecs(player, enemyRect);
			if (IsEnemyHitByProjectile)
			{
				return enemy;
			}
		}
	}
	return nullptr;
}
