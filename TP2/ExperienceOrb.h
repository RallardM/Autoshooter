#pragma once
#include "GameObject.h"

class ExperienceOrb : public GameObject
{
	friend class Enemy;

public:  // Public member variables
	unsigned short int m_id = 0;

private: // Private member variables
	float m_radius = 10.0f;

	static unsigned short int s_id;

public: // Public methods

private: // Private methods
	ExperienceOrb(const Vector2& origin);
	~ExperienceOrb()override;

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	void Reset() override;
	virtual const bool IsActive() const override { return m_isActive; }
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ORB; }
	
	void Collision();

	const float& GetRadius() const { return m_radius; }
};