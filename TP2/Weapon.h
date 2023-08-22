#pragma once

#include "GameObject.h"
#include "Projectile.h"

struct SWeaponData
{
public:
	float m_attackRate = 1.0f;
	SProjectileData m_projectileInfos;
};

class Weapon : public GameObject
{
	friend class Player;

protected: // Protected member variables
	SWeaponData m_weaponInfos;
	float m_currentAttackTimer = 0.0f;
	Color m_color = { 255, 255, 255, 255 };
	Vector2 m_size = { 5.0f, 5.0f };

protected: // Protected methods
	virtual void OnStart() = 0;

	const SWeaponData GetWeaponInfos() const { return m_weaponInfos; }
	const void SetProjectileInfos(const SProjectileData& projectileInfos) { m_weaponInfos.m_projectileInfos = projectileInfos; }

public:  // Public member variables
	unsigned short int m_weaponId = 0;

private: // Private member variables
	static unsigned short int s_weaponId;

public: // Public methods
	Weapon();
	virtual ~Weapon() = 0;

private: // Private methods
	virtual const void Fire() = 0;
	virtual void Update(const float& deltatime) = 0;
	virtual const void FollowPosition(Vector2& newPosition) override;
	virtual const void Render() = 0;
	virtual const bool IsActive() const = 0;
	virtual void Reset() = 0;

	const void IncreaseRate();
	const void IncreaseProjectileDamage();
	const void IncreaseProjectileSize();
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;

};