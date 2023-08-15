#pragma once
#include <list>
#include "Weapon.h"
#include "UIElement.h"

/**
 * @brief Represent the player
*/
class Player : public Entity
{
	friend class Game;// Allow game class to access encapsulated method and member of player class

public:
	/**
	 * @brief Default constructor
	*/
	~Player();
	/**
	 * @brief Method overriden to get player possition
	 * @return Vector2 reference of player position
	*/
	virtual const Vector2& GetPosition() const override { return m_position; }
	/**
	 * @brief Method overriden to get player game object type
	 * @return EGameObjectType player type
	*/
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PLAYER; }
	/**
	 * @brief Method overriden to get player health
	 * @return Health of the player
	*/
	virtual const short int GetHealth() const override { return m_health; }
	/**
	 * @brief Method overrident to get player max health
	 * @return Max health of player
	*/
	virtual const short int GetMaxHealth() const override { return MAX_HEALTH; }
	/**
	 * @brief Method to get Rectangle
	 * @return Player rectangle
	*/
	const Rectangle GetRect() const { return { m_position.x, m_position.y, m_playerSize.x, m_playerSize.y }; }
	
private:
	UIElement* m_healthBar = nullptr;
	UIElement* m_secondHealthBar = nullptr;
	UIElement* m_experienceText = nullptr;
	UIElement* m_experienceBar = nullptr;

	// Player default parameter
	Color m_color = PLAYER_COLOR;
	Vector2 m_playerSize = PLAYER_SIZE;
	Vector2 m_direction = PLAYER_DIRECTION;
	const float PLAYER_SPEED = PLAYER_SPEED;

	
	unsigned short int m_experience = 0;
	unsigned short int m_totalExperience = 0;
	unsigned short int m_level = PLAYER_SPEED;
	unsigned short int m_previousEnemyId = 0;

	std::list<Weapon*> m_weapons;

private:
	/**
	 * @brief Method to get the input
	*/
	void HandleInput();

	// Inherited via GameObject

	/**
	 * @brief Method overriden call when player is instantiate
	*/
	virtual void OnStart() override;
	/**
	 * @brief Method overriden call every frame 
	 * @param deltatime represent the elapsed time between frame
	*/
	virtual void Update(float deltatime) override;
	/**
	 * @brief Method overriden to render player
	*/
	virtual void Render() override;
	/**
	 * @brief Method overriden to get player state
	 * @return Player state
	*/
	virtual const bool IsActive() const override { return m_isActive; }
	/**
	 * @brief Method to reinitialize player attributes
	*/
	virtual void Reset() override;
	/**
	 * @brief Method to hangle player collision
	*/
	void Collision();
	/**
	 * @brief Method to verify player health
	*/
	void VerifyHealth();
	/**
	 * @brief Method to verify player experience
	*/
	void VerifyExperience();
	/**
	 * @brief Method to increase weapon rate damage
	*/
	void IncreaseWeaponRate();
	/**
	 * @brief Method to increase projectile damage
	*/
	void IncreaseProjectileDamage();
	/**
	 * @brief Method to increase projectile size
	*/
	void IncreaseProjectileSize();
	/**
	 * @brief Method to increase player health
	*/
	void IncreaseHealth();
	/**
	 * @brief Method to add HandGun to player
	*/
	void AddNewHandGun();
	/**
	 * @brief Method to add ExplosiveGun to player
	*/
	void AddNewExplosiveGun();
	/**
	 * @brief Method to add LaserGun to player
	*/
	void AddNewLaserGun();
};