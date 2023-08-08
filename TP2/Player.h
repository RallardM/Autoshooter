#pragma once
#include "GameObject.h"
class Weapon;

class Player : public GameObject
{
	
public:
	Player();
	Player(float& x, float& y, int& width, int& height);
	~Player();

public:
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_speed = PLAYER_SPEED;

	// Dimension
	int m_width = PLAYER_WIDTH;
	int m_height = PLAYER_HEIGHT;


	// BoxCollider
	BoxCollider m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	BoxCollider m_oldBoxCollider = m_boxCollider;
	

	Color m_color = { 0, 255, 0, 255 };
	bool m_isCollide = false;
	
	std::list<Weapon*> m_weapons;
public:

	// Inherited via Agent
	void OnStart() override;
	void HandleInput();
	void Update(float deltatime) override;
	void Render() override;
	bool Collide(GameObject& gameObject);

};