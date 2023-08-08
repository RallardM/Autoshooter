#pragma once
#include "GameObject.h"
class Weapon;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(float& x, float& y, int& width, int& height);
	~Enemy();

public:
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_speed = MIN_ENEMY_SPEED;

	// Dimension
	int m_width = ENEMY_WIDTH;
	int m_height = ENEMY_HEIGHT;


	// BoxCollider
	BoxCollider m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	BoxCollider m_oldBoxCollider = m_boxCollider;


	Color m_color = BLUE;
	bool m_isCollide = false;

	std::list<Weapon*> m_weapons;
public:

	// Inherited via Agent
	void OnStart() override;
	void Spawn();
	void Track(float& x, float& y);
	void Update(float deltatime) override;
	void Render() override;
};
