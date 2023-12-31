#pragma once
#include <list>
#include "Weapon.h"
#include "UIElement.h"
#include "Globals.h"

class Player : public Entity
{
	friend class GameObjectPool;
	friend class Game;
	friend class CollisionManager;

public:  // Public member variables

private: // Private member variables
	UIElement* m_healthBar = nullptr;
	UIElement* m_secondHealthBar = nullptr;
	UIElement* m_experienceText = nullptr;
	UIElement* m_experienceBar = nullptr;

	// Player default parameter
	Color m_color = PLAYER_COLOR;
	Vector2 m_playerSize = PLAYER_SIZE;
	Vector2 m_direction = NO_DIRECTION;

	unsigned short int m_experience = 0;
	unsigned short int m_totalExperience = 0;
	unsigned short int m_level = PLAYER_STARTING_LEVEL;
	unsigned short int m_previousEnemyId = 0;

	std::list<Weapon*> m_weapons;

public: // Public methods
	Player();
	~Player() override;

private: // Private methods
	const Vector2& GetPosition() const override { return m_position; }
	const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PLAYER; }
	const unsigned short int GetLevel() const { return m_level; }
	const short int GetHealth() const override { return m_health; }
	const short int GetMaxHealth() const override { return MAX_HEALTH; }
	const Rectangle GetRect() const { return { m_position.x, m_position.y, m_playerSize.x, m_playerSize.y }; }

	void HandleInput();

	// Inherited via GameObject
	void OnStart() override;
	void Update(const float& deltatime) override;
	const void Render() override;
	const bool IsActive() const override { return m_isActive; }
	void Reset() override;

	const void Collision();
	const void VerifyHealth();
	const void VerifyExperience();
	const void IncreaseWeaponRate() const;
	const void IncreaseProjectileDamage() const;
	const void IncreaseProjectileSize() const;
	const void IncreaseHealth();
	const void AddNewHandGun();
	const void AddNewExplosiveGun();
	const void AddNewLaserGun();
};