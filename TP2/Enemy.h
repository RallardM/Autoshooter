#pragma once
#include "GameObject.h"
#include "BoxCollider.h"
#include <vector>

class Weapon;

class Enemy : public GameObject
{
	friend class Game;
public:
	Enemy();
	//Enemy(const float&, const float&, const bool&);
	//Enemy(const float&, const float&, const int&, const int&, const bool&);
	~Enemy();

public:
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_speed = 0.0f;

	// Dimension
	float m_width = 0;
	float m_height = 0;


	// BoxCollider
	BoxCollider m_boxCollider;
	BoxCollider m_oldBoxCollider;


	Color m_color = BLUE;
	bool m_isCollide = false;

	std::vector<Weapon*> m_weapons;
public:
	const Vector2& GetPosition() const { return m_position; }

	// Inherited via Agent
	void OnStart() override;
	void Spawn();
	
	void Update() override;
	void Render() override;

private:
	// Enemy default parameter
	const float ENEMY_WIDTH = 32.0f;
	const float ENEMY_HEIGHT = 32.0f;
	const float MAX_ENEMY_SPEED = 15.0f;
	const float MIN_ENEMY_SPEED = 5.0f;

private:
	void TrackPlayer();
	void Collision();

};
