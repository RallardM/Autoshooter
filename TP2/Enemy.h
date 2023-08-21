#pragma once
#include "Entity.h"
#include "UIElement.h"
#include "Projectile.h"
#include "Globals.h"

class Weapon;

class Enemy : public Entity
{
	friend class GameObjectPool;
	friend class Projectile;
	friend class Enemy;
	friend class CollisionManager;

public:
	Enemy();
	~Enemy() override;

private:

	// Enemy default parameter
	Vector2 m_enemySize = ENEMY_SIZE;
	Vector2 m_direction = NO_DIRECTION;
	Vector2 m_previousPosition = NO_POSITION;
	Color m_color = ENEMY_DEFAULT_COLOR;
	
	unsigned short int m_previousProjectileId = 0;
	static unsigned short int s_id;
	bool m_isActive = false;

public:
	unsigned short int m_id;

private:
	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	//virtual const void FollowPosition(Vector2& newPosition) override;

	void Spawn();
	virtual const Vector2& GetPosition() const override { return m_position; }
	const Rectangle GetRect() const { return { m_position.x, m_position.y, m_enemySize.x, m_enemySize.y }; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ENEMY; }
	virtual const short int GetHealth() const override { return m_health; }
	virtual const short int GetMaxHealth() const override { return MAX_HEALTH; }

	void UpdatePosition(const float& deltatime);
	void TrackPlayer();
	void Collision();
	void VerifyHealth();
	void GenerateXPOrb();
};
