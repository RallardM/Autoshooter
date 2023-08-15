#pragma once
#include "Weapon.h"

/**
 * @brief Represent HandGun 
*/
class HandGun : public Weapon
{
private:
	static float s_uiOffsetRight;
	float m_uiOffset = 0.0f;

	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

public:
	HandGun();
	~HandGun() override;
	using Weapon::GetWeaponInfos;

private:
	// Inherited via Weapon
	/**
	 * @brief Method overriden call when weapon fire
	*/
	virtual void Fire() override;

	// Inherited via GameObject
	/**
	 * @brief Method overriden to reinitialize attributes
	*/
	virtual void Reset() override;

public:
	// Inherited via GameObject
	/**
	 * @brief Method overriden call when hand gun is instantiate
	*/
	virtual void OnStart() override;
	/**
	 * @brief Method overriden call every frame
	 * @param deltatime represent elapsed time between frame
	*/
	virtual void Update(float deltatime) override;
	/**
	 * @brief Method overriden call to render Explosive
	*/
	virtual void Render() override;
	/**
	 * @brief Method overriden to get HandGun current state
	 * @return HandGun current state
	*/
	virtual const bool IsActive() const override { return m_isActive; }
	/**
	 * @brief Method overriden to get handGun position
	 * @return Vector2 reference of handGun position
	*/
	virtual const Vector2& GetPosition() const override { return m_position; }
	/**
	 * @brief Method overriden get hand gun object type
	 * @return EGameObjectType of the hand gun
	*/
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::WEAPON; }

	/**
	 * @brief Method to get weapon type
	 * @return EWeaponType of the weapon type
	*/
	virtual const EWeaponType GetWeaponType() const { return EWeaponType::HAND_GUN; } // TODO : Make pure virtual
};