#include <iostream>

#include "CollisionManager.h"
#include "GameObjectPool.h"

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

const bool CollisionManager::AreEnemyProjectileColliding(const Rectangle& enemy) const
{
	for (GameObject* gameObject : GameObjectPool::GetInstance()->GetGameObjects())
	{
		if (gameObject == nullptr) { continue; }

		if (gameObject->GetGameObjectType() == EGameObjectType::PROJECTILE)
		{
			Projectile* projectile = dynamic_cast<Projectile*>(gameObject);
			Vector2 projectilePosition = projectile->GetPosition();

			// The collision is checked with the radius and not considering the multiple shapes of each projectile
			// it is not precise but it is faster in computation, less code for almost the same, and it is enough for not nothicing in game 
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

const Projectile* CollisionManager::GetCollidingProjectile(const Rectangle& enemy) const
{
	for (GameObject* gameObject : GameObjectPool::GetInstance()->GetGameObjects())
	{
		if (GameObjectPool::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::PROJECTILE)
		{
			Projectile* projectile = dynamic_cast<Projectile*>(gameObject);
			Vector2 projectilePosition = projectile->GetPosition();

			// The collision is checked with the radius and not considering the multiple shapes of each projectile
			// it is not precise but it is faster in computation, less code for almost the same, and it is enough for not nothicing in game  
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

const bool CollisionManager::AreOrbPlayerColliding(const Vector2& orbPosition, const float& orbradius) const
{
	bool isPlayerTouchingOrb = CheckCollisionCircleRec(orbPosition, orbradius, GameObjectPool::GetInstance()->GetPlayer()->GetRect());
	if (isPlayerTouchingOrb)
	{
		return true;
	}
	return false;
}

const bool CollisionManager::ArePlayerEnemyColliding(const Rectangle& player) const
{
	for (GameObject* gameObject : GameObjectPool::GetInstance()->GetGameObjects())
	{
		if (gameObject == nullptr) { continue; }

		if (GameObjectPool::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::ENEMY)
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

Enemy* CollisionManager::GetCollidingEnemy(const Rectangle& player) const
{
	for (GameObject* gameObject : GameObjectPool::GetInstance()->GetGameObjects())
	{
		if (GameObjectPool::GetInstance()->GetGameObjectType(gameObject) == EGameObjectType::ENEMY)
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