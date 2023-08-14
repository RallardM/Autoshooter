#pragma once
#include <raylib.h>
#include "Projectile.h"


class CollisionManager
{
public:
	static CollisionManager* GetInstance();

	// Collision detection
	bool AreEnemyProjectileColliding(Rectangle enemy);
	Projectile* GetCollidingProjectile(Rectangle enemy);
	bool AreOrbPlayerColliding(Vector2 orbPosition, float orbradius);
	bool ArePlayerEnemyColliding(Rectangle player);
	Enemy* GetCollidingEnemy(Rectangle player);

private:
	static CollisionManager* _Instance;
private:
	CollisionManager() {} // Private constructor for singleton pattern
};

