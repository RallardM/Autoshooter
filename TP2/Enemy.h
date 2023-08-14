#pragma once
#include "Entity.h"
#include "UIElement.h"
#include "Projectile.h"

class Weapon;

class Enemy : public Entity
{
	friend class Game;
public:
	Enemy();
	~Enemy();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual const bool IsActive() const override { return m_isActive; }
	virtual void Reset() override;

	void Spawn();
	virtual const Vector2& GetPosition() const override { return m_position; }
	const Rectangle GetRect() const  { return { m_position.x, m_position.y, m_enemySize.x, m_enemySize.y }; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ENEMY; }
	virtual const short int GetHealth() const override { return m_health; }
	virtual const short int GetMaxHealth() const override { return MAX_HEALTH; }

private:
	UIElement* m_healthBar = nullptr;

	// Enemy default parameter
	Vector2 m_enemySize = { 32.0f, 32.0f };
	Vector2 m_direction = { 0.0f, 0.0f };
	Vector2 m_previousPosition = { 0.0f, 0.0f };
	const float SPEED = 100.0f;
	Color m_color = BLUE;
	
	unsigned short int m_previousProjectileId = 0;
	static unsigned short int s_id;

public:
	unsigned short int m_id;

private:
	void UpdatePosition(float deltatime);
	void TrackPlayer();
	void Collision();
	void VerifyHealth();
	void GenerateXPOrb();
};
