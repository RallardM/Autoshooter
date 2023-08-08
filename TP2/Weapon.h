#pragma once
#include "GameObject.h"
class Projectile;

class Weapon : public GameObject
{
public:
	std::vector<Projectile*> m_projectiles;
	FireMode m_fireMode = FireMode::Auto;
	

public: 
	Weapon();
	Weapon(const float&, const float&, const FireMode&, const bool&);
	~Weapon();

	void OnStart();
	void Fire();
	void CreateProjectiles();
	void FireProjectiles();
	void ResetProjectile(Projectile* projectile);
	void FireProjectile(Projectile* projectile);
	void UpdatePosition(float& x, float& y);
	void Update(float deltatime);
	void Render();
};