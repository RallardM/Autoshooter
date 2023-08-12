#pragma once
#include "GameObject.h"

#include <vector>

class Weapon;

class Enemy : public GameObject
{
	friend class Game;
public:
	Enemy();
	~Enemy();

public:
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_speed = 0.0f;

	Color m_color = BLUE;
	bool m_isCollide = false;

	std::vector<Weapon*> m_weapons;

public:

	// Inherited via GameObject
	void OnStart() override;
	void Spawn();
	
	void Update() override;
	void Render() override;

	virtual const Vector2& GetPosition() const override { return m_position; }
	const Rectangle GetRect() const  { return { m_position.x, m_position.y, m_enemySize.x, m_enemySize.y }; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ENEMY; }
	const short int GetHealth() const { return m_health; }

private:
	// Enemy default parameter
	Vector2 m_enemySize = { 32.0f, 32.0f };
	const float MAX_ENEMY_SPEED = 15.0f;
	const float MIN_ENEMY_SPEED = 5.0f;

	short int m_health = 100;

private:
	void TrackPlayer();
	void Collision();
	void VerifyHealth();
	void GenerateXPOrb();
};
