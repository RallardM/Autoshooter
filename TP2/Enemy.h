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
	//float m_width = 0;
	//float m_height = 0;
	


	// BoxCollider
	BoxCollider m_boxCollider;
	BoxCollider m_oldBoxCollider;


	Color m_color = BLUE;
	bool m_isCollide = false;

	std::vector<Weapon*> m_weapons;
	//EGameObjectType m_gameObjectType;
public:

	// Inherited via Agent
	void OnStart() override;
	void Spawn();
	
	void Update() override;
	void Render() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	const Rectangle GetRect() const  { return { m_position.x, m_position.y, ENEMY_WIDTH, ENEMY_HEIGHT }; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ENEMY; }

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
