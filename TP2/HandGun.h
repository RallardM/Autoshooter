#pragma once
#include "Weapon.h"

struct SWeaponData
{
public:
	float m_attackRate = 1.0f;
	SHandGunProjectileData m_projectileInfos;
};

class HandGun : public Weapon
{
	friend class Game;
private:

	float m_currentAttackTimer = 0.0f;
	SWeaponData m_weaponInfos;
	Vector2 m_size = { 5.0f, 5.0f };
	EGameObjectType m_gameObjectType;

private:
	virtual void Fire() override;
	
public:
	HandGun();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return m_gameObjectType; }
};