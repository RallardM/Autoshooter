#pragma once
#include <raylib.h>

#include "Agent.h"

class Projectile : public Agent
{
	friend class Game;
private:
	float m_currentLifetime;
	float m_xSpeed;
	float m_ySpeed;
	float m_radius;
	Color m_color;

public:
	Projectile(float xSpeed, float ySpeed, float size, float lifetime);

	// Inherited via Agent
	virtual void OnStart() override;
	virtual void Update() override;
};

struct SProjectileData
{
public:
	float Radius = 5.0f;
	float Lifetime = 2.0f;
	float Damage = 10.0f;
};