#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "BoxCollider.h"

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
	Projectile(float xSpeed, float ySpeed, float size, float lifetime);
	~Projectile();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
};

struct SProjectileData
{
public:
	float Radius = 5.0f;
	float Lifetime = 2.0f;
	float Damage = 10.0f;
};