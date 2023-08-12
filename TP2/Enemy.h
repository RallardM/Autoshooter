#pragma once
#include "GameObject.h"
#include "UIElement.h"

#include <vector>

class Weapon;

class Enemy : public GameObject
{
	friend class Game;
public:
	Enemy();
	~Enemy();

public:

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() override { return m_isActive; }
	virtual void Reset() override;

	void Spawn();
	virtual const Vector2& GetPosition() const override { return m_position; }
	const Rectangle GetRect() const  { return { m_position.x, m_position.y, m_enemySize.x, m_enemySize.y }; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ENEMY; }
	const short int GetHealth() const { return m_health; }


private:
	UIElement* m_healthBar = nullptr;

	// Enemy default parameter
	Vector2 m_enemySize = { 32.0f, 32.0f };
	Vector2 m_direction = { 0.0f, 0.0f };
	Vector2 m_previousPosition = { 0.0f, 0.0f };
	const float SPEED = 100.0f;
	Color m_color = BLUE;
	short int m_health = 100;
	static unsigned short int s_id;

public:
	unsigned short int m_id;

private:
	void TrackPlayer();
	void Collision();
	void VerifyHealth();
	void GenerateXPOrb();
};
