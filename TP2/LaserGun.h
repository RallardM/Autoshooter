#pragma once
#include "Weapon.h"

class LaserGun : public Weapon
{
	friend class Player;

private:
	static float s_uiOffsetRight; // TODO Remi : move to UIElement
	float m_uiOffset = 0.0f; // TODO Remi : move to UIElement

	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

	bool m_isSetToDestroy = false;

public:
	LaserGun();
	~LaserGun() override;

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
};

