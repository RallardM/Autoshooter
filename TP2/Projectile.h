#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile();
	Projectile(const float&, const float&, const float&, const float&);
	Projectile( const float&, const float&, const float&, const float&, const int&, const int&, const bool&);
	~Projectile();

	Vector2 m_originPosition = { 0.0f, 0.0f };// Use to memorise the intial position of the projectile when is generate before being translate to the center use to reset position of projectile to player position
	Vector2 m_initDirection = { 0.0f, 0.0f};// Use to set the initial direction when the projectile is generate
	Vector2 m_direction = { 0.0f, 0.0f };// Use to set the direction of the projectile 
	float m_speed = 0.0f;// Projectile speed
	float m_lifeTime = 0.0f;// Life time before projectile is destroy if is not touch any obstacle

	// Dimension
	int m_width = 0;
	int m_height = 0;


	// BoxCollider
	BoxCollider m_boxCollider;
	BoxCollider m_oldBoxCollider;


	Color m_color = RED;
	bool m_isCollide = false;

public:
	void OnStart();
	void Reload(float& x, float& y);
	void Fire();
	void Update(float deltatime);
	void Render();
};