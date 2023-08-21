#pragma once
#include "Weapon.h"

class HandGun : public Weapon
{
	friend class Player;
	friend class GameObjectPool;

private:
	static float s_uiOffsetRight;
	float m_uiOffset = 0.0f;

	static unsigned short int s_id;
	bool m_isActive = false;

public:
	unsigned short int m_id = 0;

public:
	HandGun();
	~HandGun() override;

private:
	// Inherited via Weapon
	virtual void Fire() override;
	virtual void Reset() override;
	virtual void OnStart() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() const override { return m_isActive; }
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::WEAPON; }
	virtual const EWeaponType GetWeaponType() const override { return EWeaponType::HANDGUN; }
};