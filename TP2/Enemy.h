#pragma once
#include "GameObject.h"
class Weapon;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(const float&, const float&, const bool&);
	Enemy(const float&, const float&, const int&, const int&, const bool&);
	~Enemy();

public:
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_speed = 0.0f;

	// Dimension
	int m_width = 0;
	int m_height = 0;


	// BoxCollider
	BoxCollider m_boxCollider;
	BoxCollider m_oldBoxCollider;


	Color m_color = BLUE;
	bool m_isCollide = false;

	std::vector<Weapon*> m_weapons;
public:

	// Inherited via Agent
	void OnStart() override;
	void Spawn();
	void Track(float& x, float& y);
	void Update(float deltatime) override;
	void Render() override;
};
