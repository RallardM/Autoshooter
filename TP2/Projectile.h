#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "BoxCollider.h"
#include "Enemy.h"

class Projectile : public GameObject
{
	friend class Game;

private:
	float m_currentLifetime;
	float m_xSpeed;
	float m_ySpeed;
	float m_radius;
	Color m_color;

	// BoxCollider
	BoxCollider* m_boxCollider;
	// TODO Remi : Vérifier code ajouté par Maurice:
	//BoxCollider m_previousBoxCollider;

public:
	
	Projectile(Vector2 origin, float size, float speed, float lifetime);
	~Projectile();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	Enemy* FindClosestEnemyToPlayer();

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
