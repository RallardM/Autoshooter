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
	const bool AreEnemyProjectileColliding(const Rectangle& enemy) const;
	const Projectile* GetCollidingProjectile(const Rectangle& enemy) const;
	const bool AreOrbPlayerColliding(const Vector2& orbPosition, const float& orbradius) const;
	const bool ArePlayerEnemyColliding(const Rectangle& player) const;
	Enemy* GetCollidingEnemy(const Rectangle& player) const;
};

