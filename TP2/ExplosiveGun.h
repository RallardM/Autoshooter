#pragma once
#include "Weapon.h"

class ExplosiveGun : public Weapon
{
	friend class Player;

private:
	static float s_uiOffsetRight;
	float m_uiOffset = 0.0f;

	static unsigned short int s_id;

	bool m_isSetToDestroy = false;

public:
	unsigned short int m_id = 0;

public:
	ExplosiveGun();
	~ExplosiveGun() override;

private:
	// Inherited via Weapon
	virtual void Fire() override;
	virtual void Reset() override;
	virtual void OnStart() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	virtual const bool IsActive() const override { return m_isActive; }
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::WEAPON; }
	virtual const bool GetIsSetToDestroy() const override { return m_isSetToDestroy; }

	virtual const EWeaponType GetWeaponType() const { return EWeaponType::EXPLOSIVE_GUN; } // TODO : Make pure virtual
};