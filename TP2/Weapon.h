#pragma once

#include "Projectile.h"

struct SWeaponData
{
public:
	float m_attackRate = 1.0f;
	SProjectileData m_projectileInfos;
};

class Weapon: public GameObject
{
private:
	float m_currentAttackTimer = 0.0f;
	SWeaponData m_weaponInfos;

private:
	void Fire();
public:
	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
};

