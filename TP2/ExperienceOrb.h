#pragma once
#include "GameObject.h"

class ExperienceOrb : public GameObject
{
private:
	float m_radius = 10.0f;

	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

public:
	ExperienceOrb(Vector2 origin);
	~ExperienceOrb()override;

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
};

