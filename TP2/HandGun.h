#pragma once
#include "Weapon.h"

struct SWeaponData
{
public:
	float m_attackRate = 1.0f;
	SProjectileData m_projectileInfos;
};

class HandGun : public Weapon
{
private:
	float m_currentAttackTimer = 0.0f;
	SWeaponData m_weaponInfos;
	Vector2 m_size = { 5.0f, 5.0f };

private:
	virtual void Fire() override;
public:
	HandGun();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void FollowPosition(Vector2 newPosition) override;
	virtual void Render() override;
};