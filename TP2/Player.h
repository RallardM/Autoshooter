#pragma once
#include <list>
#include "Weapon.h"
#include "UIElement.h"

class Player : public Entity
{
	friend class Game;

public:
	~Player();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PLAYER; }
	const Rectangle GetRect() const { return { m_position.x, m_position.y, m_playerSize.x, m_playerSize.y }; }
	//const short int GetHealth() const { return m_health; }
	
private:
	UIElement* m_healthBar = nullptr;
	UIElement* m_experienceText = nullptr;
	UIElement* m_experienceBar = nullptr;

	// Player default parameter
	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_playerSize = { 32.0f, 32.0f };
	Vector2 m_direction = { 0.0f, 0.0f };
	const float PLAYER_SPEED = 200.0f;
	short int m_health = 100;
	unsigned short int m_experience = 0;
	unsigned short int m_totalExperience = 0;
	unsigned short int m_level = 1;

	std::list<Weapon*> m_weapons;

private:
	void HandleInput();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() override { return m_isActive; }
	virtual void Reset() override;
	void Collision();
	void VerifyHealth();
	void VerifyExperience();
	void IncreaseWeaponRate();
	void IncreaseProjectileDamage();
	void IncreaseProjectileSize();
	void IncreaseHealth();
};