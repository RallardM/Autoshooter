#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "Enemy.h"

unsigned short int SProjectileData::s_projectileDataId = 0;
struct SProjectileData
{
private:
	static unsigned short int s_projectileDataId;

public:
	Color COLOR;
	Vector2 DIRECTION;
	Vector2 POSITION;
	float RADIUS;
	float LIFETIME;
	float DAMAGE;
	float SPEED;
	short int COUNT_DOWN;
	EWeaponType WEAPON_TYPE;
	unsigned short int ID = 0;
	SProjectileData(const Color color, const Vector2 direction, const Vector2 position, const float radius, const float lifetime, const float damage, const float speed, const short int countDown, const EWeaponType weaponType)
		: COLOR(color), DIRECTION(direction), POSITION(position), RADIUS(radius), LIFETIME(lifetime), DAMAGE(damage), SPEED(speed), COUNT_DOWN(countDown), WEAPON_TYPE(weaponType)
	{
		ID = s_projectileDataId++;
	}
};

class Projectile : public GameObject
{
	friend class GameObjectPool;
	friend class CollisionManager;
	friend class Enemy;
	friend class ExplosiveGun;
	friend class HandGun;
	friend class LaserGun;

private:
	// Keep the member variables as low as possible so the objects are very light
	float& m_radius;
	SProjectileData* m_projectileData;

	// Dynamic, does not work as references
	float m_currentLifetime = 0.0f;
	float m_xSpeed = 0.0f;
	float m_ySpeed = 0.0f;

	static unsigned short int s_id;

	bool m_isActive = false;

public:
	unsigned short int m_id = 0;

public:
	Projectile(SProjectileData* projectileData);
	~Projectile() override;

private:
	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PROJECTILE; }

	const float& GetRadius() const { return m_radius; }
	const float GetDamage() const { return m_projectileData->DAMAGE; }

	const void SetProjectileInfos(SProjectileData* projectileData) { m_projectileData = projectileData; }
	const void SetHandGunProjectileData();
	const void SetExplosiveGunProjectileValues();
	const void SetLaserGunProjectileValues();
	const void SendInRandomDirections();
};
