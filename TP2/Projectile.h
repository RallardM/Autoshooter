#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(float& x, float& y, float& dx, float& dy);

	Vector2 m_originPosition = { 0.0f, 0.0f };// Use to memorise the intial position of the projectile when is generate before being translate to the center use to reset position of projectile to player position
	Vector2 m_initDirection = { 0.0f, 0.0f};// Use to set the initial direction when the projectile is generate
	Vector2 m_direction = { 0.0f, 0.0f };// Use to set the direction of the projectile 
	float m_speed = PROJECTILE_SPEED;// Projectile speed
	float m_lifeTime = 0.0f;// Life time before projectile is destroy if is not touch any obstacle

	// Dimension
	int m_width = PROJECTILE_WIDTH;
	int m_height = PROJECTILE_HEIGHT;


	// BoxCollider
	BoxCollider m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	BoxCollider m_oldBoxCollider = m_boxCollider;


	Color m_color = { 255, 0, 0, 255 };
	bool m_isCollide = false;

public:
	void OnStart();
	void Reset(float& x, float& y);
	void Launch();
	void Update(float deltatime);
	void Render();
};