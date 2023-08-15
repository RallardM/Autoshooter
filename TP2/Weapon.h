#pragma once

#include "GameObject.h"
#include "Projectile.h"

/**
 * @brief Represent weapon data
*/
struct SWeaponData
{
public:
	float m_attackRate = 2.0f;
	SProjectileData m_projectileInfos;
};

/**
 * @brief Abstract class that represent a weapon
*/
class Weapon : public GameObject
{
	friend class Player;// Allow player class to access encapsulated method or member of weapon class

private:
	/**
	 * @brief Abstract method call when weapon fire
	*/
	virtual void Fire() = 0;
	/**
	 * @brief Abstract method call every frame
	 * @param deltatime represent elapsed time passed between two frame
	*/
	virtual void Update(float deltatime) = 0;
	/**
	 * @brief Method that update weapon position based on element its attached
	 * @param newPosition 
	*/
	void FollowPosition(Vector2 newPosition); // TODO make pure virtual
	/**
	 * @brief Abstract methoc call to render the weapon
	*/
	virtual void Render() = 0;
	/**
	 * @brief Abstract method that get current weapon state
	 * @return state of the weapon
	*/
	virtual const bool IsActive() const = 0;
	/**
	 * @brief Abstract method called to reinitialize weapon attributes 
	*/
	virtual void Reset() = 0;

protected:
	/**
	 * @brief Abstract method call when weapon is initialize
	*/
	virtual void OnStart() = 0;
	/**
	 * @brief Method to increase weapon attack rate
	*/
	void IncreaseRate();
	/**
	 * @brief Method to increase projectile damage rate
	*/
	void IncreaseProjectileDamage();
	/**
	 * @brief Method to increase projectile size
	*/
	void IncreaseProjectileSize();
	/**
	 * @brief Abstract method that get weapon position
	 * @return Vector2 position of the weapon
	*/
	virtual const Vector2& GetPosition() const = 0;
	/**
	 * @brief Abstract method that get game object type
	 * @return EGameObjectType type of the weapon
	*/
	virtual const EGameObjectType GetGameObjectType() const = 0;
	/**
	 * @brief Abstract method that get weapon informations
	 * @return SWeaponData data of the weapon
	*/
	const SWeaponData GetWeaponInfos() const { return m_weaponInfos; }
	/**
	 * @brief Abstract method that get projectile informations
	 * @return SProjectileData data of the projectile 
	*/
	SProjectileData& GetProjectileInfos() { return m_weaponInfos.m_projectileInfos; }
	void SetProjectileInfos(const SProjectileData& projectileInfos) { m_weaponInfos.m_projectileInfos = projectileInfos; }

protected:
	SWeaponData m_weaponInfos;
	Color m_color = { 255, 255, 255, 255 };
};