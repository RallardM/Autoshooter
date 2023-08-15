#pragma once
#include <raylib.h>

#include "GameObject.h"
#include "Enemy.h"

/**
 * @brief Represent projectile data 
*/
struct SProjectileData
{
public:

	float RADIUS = PROJECTILE_RADIUS;
	float LIFETIME = PROJECTILE_LIFETIME;
	float DAMAGE = PROJECTILE_DAMAGE;
	float SPEED = PROJECTILE_SPEED;
	Color COLOR = PROJECTILE_COLOR;
	EWeaponType WEAPON_TYPE = EWeaponType::COUNT;
};

/**
 * @brief Represent a projectile
*/
class Projectile : public GameObject
{
	friend class Game;// Allow game class to acess encapsulated method and memeber of projectile

public:
	unsigned short int m_id;

private:
	Vector2 m_direction = { 0.0f, 0.0f };
	float m_currentLifetime = 0.0f;
	float m_xSpeed = 0.0f;
	float m_ySpeed = 0.0f;
	float m_radius = 0.0f;
	Color m_color = { 255, 255, 255, 255 };
	SProjectileData& m_projectileData;
	static unsigned short int s_id;

public:
	/**
	 * @brief Constructor of projectile
	 * @param projectileData data of projectile
	 * @param origin initial position value
	 * @param direction initial direction 
	*/
	Projectile(SProjectileData& projectileData, Vector2& origin, Vector2& direction);

	// Inherited via GameObject
	
	/**
	 * @brief Method overriden call when projectile is instantiate
	*/
	virtual void OnStart() override;
	/**
	 * @brief Method overriden call every frame
	 * @param deltatime represent the time elapsed between frame
	*/
	virtual void Update(float deltatime) override;
	/**
	 * @brief Method overriden call to render projectile
	*/
	virtual void Render() override;
	/**
	 * @brief Method overriden to get the projectile state
	 * @return The projectile state 
	*/
	virtual bool const IsActive() const override { return m_isActive; }
	/**
	 * @brief Method overriden to reset/ 0
	*/
	virtual void Reset() override;
	/**
	 * @brief Method overriden to get projectile position 
	 * @return Vector2 reference position of the projectile
	*/
	virtual const Vector2& GetPosition() const override { return m_position; }
	/**
	 * @brief Method overrident to get projectile radius
	 * @return Raduis of the projectile
	*/
	const float& GetRadius() const { return m_radius; }
	/**
	 * @brief Method overriden to get projectile type
	 * @return EGameObjectType the game object type of the projectile
	*/
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PROJECTILE; }
	/**
	 * @brief Method overriden to get projectile damage
	 * @return Damage of he projectile
	*/
	const float GetDamage() const { return m_projectileData.DAMAGE; }
	/**
	 * @brief Method overriden to get projectile lifeTime
	 * @return Projectile life time
	*/
	const float GetCurrentLifetime() const { return m_currentLifetime; }

private:
	/**
	 * @brief Method to set HandGun projectile data
	 * @param projectileData represent the data of the projectile
	*/
	void SetHandGunProjectileData(SProjectileData& projectileData);
	/**
	 * @brief Method to set ExplosiveGun projectile data
	 * @param projectileData represent the data of the projectile
	 * @param direction represent the direction of the projectile
	*/
	void SetExplosiveGunProjectileValues(SProjectileData& projectileData, Vector2& direction);
	/**
	 * @brief Method to set LaserGun projectile data
	 * @param projectileData represent the data of the projectile
	 * @param projectileData represent the direction of the projectile
	*/
	void SetLaserGunProjectileValues(SProjectileData& projectileData);
};
