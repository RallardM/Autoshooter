#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "Enemy.h"

struct SProjectileData
{
public:

	float RADIUS = 5.0f;
	float LIFETIME = 2.0f;
	float DAMAGE = 10.0f;
	float SPEED = 300.0f;
	Color COLOR = { 255, 255, 255, 255 };
	EWeaponType WEAPON_TYPE = EWeaponType::COUNT;
};

class Projectile : public GameObject
{
	friend class Game;

public:
	unsigned short int m_id;

private:

	float m_currentLifetime = 0.0f;
	float m_xSpeed = 0.0f;
	float m_ySpeed = 0.0f;
	float m_radius = 0.0f;
	Color m_color = { 255, 255, 255, 255 };
	SProjectileData& m_projectileData;
	static unsigned short int s_id;

public:
	
	Projectile(SProjectileData& projectileData, Vector2& origin);

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual bool const IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	const float& GetRadius() const { return m_radius; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PROJECTILE; }
	const float GetDamage() const { return m_projectileData.DAMAGE; }
	const float GetCurrentLifetime() const { return m_currentLifetime; }

private:
	void SetHandGunProjectileData(SProjectileData& projectileData);
	void SetExplosiveGunProjectileValues(SProjectileData& projectileData);
	void SetLaserGunProjectileValues(SProjectileData& projectileData);
};
