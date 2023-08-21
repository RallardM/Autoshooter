#pragma once
#include <raylib.h>
#include "Projectile.h"


class CollisionManager
{
	friend class Enemy;
	friend class Player;
	friend class ExperienceOrb;

public:
	~CollisionManager();
	static CollisionManager* GetInstance();

private:
	static CollisionManager* _Instance;
private:
	CollisionManager(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I

	// Collision detection
	bool AreEnemyProjectileColliding(const Rectangle& enemy);
	Projectile* GetCollidingProjectile(const Rectangle& enemy);
	bool AreOrbPlayerColliding(const Vector2& orbPosition, const float& orbradius);
	bool ArePlayerEnemyColliding(const Rectangle& player);
	Enemy* GetCollidingEnemy(const Rectangle& player);
};

