#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "Enemy.h"

struct SProjectileData
{
public:
	Color COLOR;
	Vector2 DIRECTION;
	//Vector2 POSITION;
	float RADIUS;
	float LIFETIME;
	float DAMAGE;
	float SPEED;
	EWeaponType WEAPON_TYPE;
	SProjectileData() = default;
	SProjectileData(float radius, float lifetime, float damage, float speed, Vector2 direction, /*Vector2 position,*/ Color color, EWeaponType weaponType)
		: RADIUS(radius), LIFETIME(lifetime), DAMAGE(damage), SPEED(speed), DIRECTION(direction), /*POSITION(position),*/ COLOR(color), WEAPON_TYPE(weaponType)
	{
	}
};

class Projectile : public GameObject
{
private:
	// Keep the member variables as low as possible so the objects are very light
	//Vector2 m_direction = { 0.0f, 0.0f };
	float m_currentLifetime = 0.0f;
	float m_xSpeed = 0.0f;
	float m_ySpeed = 0.0f;
	float& m_radius;
	//Color m_color = { 255, 255, 255, 255 };
	SProjectileData& m_projectileData;
	short int m_laserBounces = 2;

	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

public:
	Projectile(SProjectileData& projectileData, Vector2& position);
	~Projectile() override;

	// Inherited via GameObject
	virtual void OnStart() override;

	virtual void Update(float& deltatime) override;

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
