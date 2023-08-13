#pragma once

#include "GameObject.h"
#include "Projectile.h"


struct SWeaponData
{
public:
	float m_attackRate = 1.0f;
	SHandGunProjectileData m_projectileInfos;
};


class Weapon : public GameObject
{
	friend class Player;
public:

private:
	virtual void Fire() = 0;
	virtual void IncreaseRate()= 0;
	virtual void OnStart() = 0;
	virtual void Update(float deltatime) = 0;
	void FollowPosition(Vector2 newPosition); // TODO make pure virtual
	virtual void Render() = 0;
	virtual bool IsActive() = 0;
	virtual void Reset() = 0;
	virtual void IncreaseProjectileDamage() = 0;
	virtual void IncreaseProjectileSize() = 0;


protected:
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;
};


