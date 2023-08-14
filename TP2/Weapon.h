#pragma once

#include "GameObject.h"
#include "Projectile.h"


struct SWeaponData
{
public:
	float m_attackRate = 2.0f;
	SProjectileData m_projectileInfos;
};


class Weapon : public GameObject
{
	friend class Player;

private:
	virtual void Fire() = 0;
	virtual void OnStart() = 0;
	virtual void Update(float deltatime) = 0;
	void FollowPosition(Vector2 newPosition); // TODO make pure virtual
	virtual void Render() = 0;
	virtual const bool IsActive() const = 0;
	virtual void Reset() = 0;

protected:
	void IncreaseRate();
	void IncreaseProjectileDamage();
	void IncreaseProjectileSize();
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;
	const SWeaponData GetWeaponInfos() const { return m_weaponInfos; }
	SProjectileData& GetProjectileInfos() { return m_weaponInfos.m_projectileInfos; }
	void SetProjectileInfos(const SProjectileData& projectileInfos) { m_weaponInfos.m_projectileInfos = projectileInfos; }

private:
	SWeaponData m_weaponInfos;

};