#pragma once
#include "Weapon.h"

class HandGun : public Weapon
{
	friend class Game;

private:
	float m_currentAttackTimer = 0.0f;
	Vector2 m_size = { 5.0f, 5.0f };

public:
	using Weapon::GetWeaponInfos;

private:
	// Inherited via Weapon
	virtual void Fire() override;

	// Inherited via GameObject
	virtual void Reset() override;

public:
	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() override { return m_isActive; }
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::WEAPON; }

};