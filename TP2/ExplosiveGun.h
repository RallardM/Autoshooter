#pragma once
#include "Weapon.h"
class Projectile;

class ExplosiveGun : public Weapon
{
public:
	std::vector<Projectile*> m_projectiles;


public:
	ExplosiveGun();
	ExplosiveGun(const float& x, const float& y);
	ExplosiveGun(const float&, const float&, const FireMode&, const bool&);
	~ExplosiveGun();

	void Load();
	void Reload();
	void Fire();
	void ReloadProjectile(Projectile* projectile);
	void FireProjectile(Projectile* projectile);
	void OnStart();
	void UpdatePosition(float& x, float& y);
	void Update(float deltatime);
	void Render();
};
