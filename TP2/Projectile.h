#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "Enemy.h"

class Projectile : public GameObject
{
	friend class Game;

public:
	unsigned short int m_id;

private:
	float m_currentLifetime;
	float m_xSpeed;
	float m_ySpeed;
	float m_radius;
	Color m_color;
	EGameObjectType m_gameObjectType;

	static unsigned short int s_id;

public:
	
	Projectile(Vector2 origin, float size, float speed, float lifetime);
	~Projectile();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Reset() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	const float& GetRadius() const { return m_radius; }
	virtual const EGameObjectType GetGameObjectType() const override { return m_gameObjectType; }

};

struct SHandGunProjectileData
{
public:
	float RADIUS = 5.0f;
	float LIFETIME = 2.0f;
	float DAMAGE = 10.0f;
	float SPEED = 20.0f;
	EWeaponType WEAPON_TYPE = EWeaponType::HAND_GUN;
};
