#pragma once
#include "Projectile.h"
class Weapon : GameObject
{
public:
	
	int m_shapeCornersNumber = 6;
	int m_radius = 64.0f;
	Vector2 m_projectilePosition = { 0.0f, 0.0f };
	float m_teta = (2 * PI) / m_shapeCornersNumber;
	float m_angle = 0.0f;

	std::vector<Projectile*> m_projectiles;

public: 
	Weapon(float& x, float& y);
	~Weapon();

	void OnStart();
	void Fire();
	void CreateProjectiles();
	void LaunchProjectiles();
	void ResetProjectile(Projectile* projectile);
	void LaunchProjectile(Projectile* projectile);
	void UpdatePosition(float& x, float& y);
	void Update(float deltatime);
	void Render();
};