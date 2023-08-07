#pragma once
#include "GameObject.h"
class Projectile;

class Weapon : public GameObject
{
public:

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