#pragma once
#include "GameObject.h"

class ExperienceOrb : public GameObject
{
	friend class GameObjectPool;
	friend class Enemy;

private:
	float m_radius = 10.0f;

	static unsigned short int s_id;

	bool m_isActive = false;

public:
	unsigned short int m_id = 0;

private:
	//ExperienceOrb(const Vector2& origin);
	ExperienceOrb();
	~ExperienceOrb()override;

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	virtual bool IsActive() const override { return m_isActive; }
	void Reset() override;
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::ORB; }
	
	const float& GetRadius() const { return m_radius; }
	void Collision();
	const void SetPosition(const Vector2& newPosition) { m_position = newPosition; }
};

