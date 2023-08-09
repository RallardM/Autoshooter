#pragma once
#include "GameObject.h"
class Projectile;

class Weapon : public GameObject
{
public:
	
	FireMode m_fireMode = FireMode::Auto;
	

public: 
	Weapon();
	Weapon(const float& x, const float& y);
	Weapon(const float&, const float&, const FireMode&, const bool&);
	virtual ~Weapon();

	virtual void Load() = 0;
	virtual void Reload() = 0;
	virtual void Fire() = 0;
	virtual void ReloadProjectile(Projectile*) = 0;
	virtual void FireProjectile(Projectile*) = 0;
	virtual void OnStart() = 0;
	virtual void UpdatePosition(float&, float&) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
};