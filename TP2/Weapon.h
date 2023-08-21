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
	friend class GameObjectPool;

private:

	static unsigned short int s_weaponId;

public:
	unsigned short int m_weaponId = 0;

public:
	Weapon();
	virtual ~Weapon() = 0;

private:
	virtual void Fire() = 0;
	virtual void Update(const float& deltatime) = 0;
	void FollowPosition(const Vector2& newPosition); // TODO make pure virtual
	virtual void Render() = 0;
	virtual const bool IsActive() const = 0;
	virtual void Reset() = 0;
	virtual const EWeaponType GetWeaponType() const = 0;

protected:
	virtual void OnStart() = 0;
	void IncreaseRate();
	void IncreaseProjectileDamage();
	void IncreaseProjectileSize();
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;
	const SWeaponData GetWeaponInfos() const { return m_weaponInfos; }
	void SetProjectileInfos(const SProjectileData& projectileInfos) { m_weaponInfos.m_projectileInfos = projectileInfos; }

protected:
	SWeaponData m_weaponInfos;
	Color m_color = { 255, 255, 255, 255 };
	float m_currentAttackTimer = 0.0f;
	Vector2 m_size = { 5.0f, 5.0f };
};