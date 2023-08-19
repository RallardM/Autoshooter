#pragma once
#include <list>
#include "Weapon.h"
#include "UIElement.h"

class Player : public Entity
{
	friend class Game;
	friend class CollisionManager;

public:
	Player();
	~Player() override;

private:
	UIElement* m_healthBar = nullptr;
	UIElement* m_secondHealthBar = nullptr;
	UIElement* m_experienceText = nullptr;
	UIElement* m_experienceBar = nullptr;

	// Player default parameter
	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_playerSize = { 32.0f, 32.0f };
	Vector2 m_direction = { 0.0f, 0.0f };
	const float PLAYER_SPEED = 200.0f;

	unsigned short int m_experience = 0;
	unsigned short int m_totalExperience = 0;
	unsigned short int m_level = 1;
	unsigned short int m_previousEnemyId = 0;

	std::list<Weapon*> m_weapons;

private:
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
	void Render() override;
	const bool IsActive() const override { return m_isActive; }
	void Reset() override;
	void Collision();
	void VerifyHealth();
	void VerifyExperience();
	void IncreaseWeaponRate();
	void IncreaseProjectileDamage();
	void IncreaseProjectileSize();
	void IncreaseHealth();
	void AddNewHandGun();
	void AddNewExplosiveGun();
	void AddNewLaserGun();
};