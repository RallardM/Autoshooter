#pragma once
#include "GameObject.h"
#include "BoxCollider.h"

class Projectile : GameObject
{
public:
	Projectile(float& x, float& y, float& dx, float& dy);

	Vector2 m_initPosition = {0.0f, 0.0f};
	Vector2 m_originPosition = { 0.0f, 0.0f };
	Vector2 m_initDirection = { 0.0f, 0.0f};
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_speed = PROJECTILE_SPEED;
	float m_lifeTime = 0.0f;

	// Dimension
	int m_width = PROJECTILE_WIDTH;
	int m_height = PROJECTILE_HEIGHT;


	// BoxCollider
	BoxCollider m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	BoxCollider m_oldBoxCollider = m_boxCollider;


	Color m_color = { 255, 0, 0, 255 };
	bool m_isCollide = false;
	bool m_isDie = false;

public:
	void OnStart();
	void Reset(float& x, float& y);
	void Launch();
	void Update(float deltatime);
	void Render();
};