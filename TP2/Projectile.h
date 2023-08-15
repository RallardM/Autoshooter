#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "Enemy.h"

struct SProjectileData
{
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
	SProjectileData() = default;
	SProjectileData(const float radius, const float lifetime, const float damage, const float speed, const short int countDown, const Vector2 direction, const Vector2 position, const Color color, const EWeaponType weaponType)
		: RADIUS(radius), LIFETIME(lifetime), DAMAGE(damage), SPEED(speed), DIRECTION(direction), COUNT_DOWN(countDown), POSITION(position), COLOR(color), WEAPON_TYPE(weaponType)
	{
	}
};

class Projectile : public GameObject
{
private:
	// Keep the member variables as low as possible so the objects are very light
	float& m_radius;
	SProjectileData& m_projectileData;

	// Dynamic, does not work as references
	float m_currentLifetime = 0.0f;
	float m_xSpeed = 0.0f;
	float m_ySpeed = 0.0f;

	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

public:
	Projectile(SProjectileData& projectileData);
	~Projectile() override;

	// Inherited via GameObject
	virtual void OnStart() override;

	virtual void Update(const float& deltatime) override;

	virtual void Render() override;

	virtual bool const IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	const float& GetRadius() const { return m_radius; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PROJECTILE; }
	const float GetDamage() const { return m_projectileData.DAMAGE; }

private:
	void SetHandGunProjectileData();
	void SetExplosiveGunProjectileValues();
	void SetLaserGunProjectileValues();
	void SendInRandomDirections();
};
