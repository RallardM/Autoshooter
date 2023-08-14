#pragma once
#include "GameObject.h"

class ExperienceOrb : public GameObject
{
public:
	ExperienceOrb(Vector2 origin);

	// Inherited via GameObject
	virtual void OnStart() override;

private:
	// Inherited via GameObject
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	virtual const bool IsActive() const override { return m_isActive; }
	void Reset() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ORB; }
	
	const float& GetRadius() const { return m_radius; }
	void Collision();

public:

private:
	float m_radius = 10.0f;
};

