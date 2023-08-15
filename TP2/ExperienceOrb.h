#pragma once
#include "GameObject.h"
/**
 * @brief Represent the orb
*/
class ExperienceOrb :
    public GameObject
{
public:
	/**
	 * @brief Constructor of orb object
	 * @param origin represent the position of the orb
	*/
	ExperienceOrb(Vector2 origin);
	/**
	 * @brief Method overriden call when object is instantiate
	*/
	virtual void OnStart() override;

private:
	// Inherited via GameObject

	/**
	 * @brief Method overriden call every frame
	 * @param deltatime represent elapsed time between frame
	*/
	virtual void Update(float deltatime) override;
	/**
	 * @brief Method overriden call to render orb
	*/
	virtual void Render() override;
	/**
	 * @brief Method overriden to get orb current state
	 * @return orb current state
	*/
	virtual const bool IsActive() const override { return m_isActive; }
	/**
	 * @brief Method overriden reinitialize all orb attributes
	*/
	void Reset() override;
	/**
	 * @brief Method overriden to get orb position
	 * @return Vector2 reference of orb position
	*/
	virtual const Vector2& GetPosition() const override { return m_position; }
	
	/**
	 * @brief Method overrident to get orb radius
	 * @return orb radius
	*/
	const float& GetRadius() const { return m_radius; }
	/**
	 * @brief Method overriden to get orb object type
	 * @return EGameObjectType type of orb
	*/
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ORB; }
	
	/**
	 * @brief Method to handle orb collision
	*/
	void Collision();

public:

private:
	float m_radius = 10.0f;
};

