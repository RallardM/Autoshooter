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
private:
	virtual void Fire() override;
	virtual void Reset() override;
	
public:
	HandGun();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() override { return m_isActive; }
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::WEAPON; }
};