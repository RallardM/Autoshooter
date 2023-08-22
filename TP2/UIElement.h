#pragma once
#include "GameObject.h"
#include "Entity.h"

class UIElement : public GameObject
{
	friend class Player;
	friend class Enemy;

private:
	Entity* m_targetEntity = nullptr;
	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_size = { 32.0f, 32.0f };
	Vector2 m_offset = { 0.0f, 0.0f };
	EUIElementType m_UIType = EUIElementType::COUNT;
	float m_floatValue = 0.0f;
	unsigned short int m_intValue = 0;
	int m_fontSize = 0;
	bool m_hasASecondBarToRegressBefore = false;

	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

public:
	UIElement(Entity* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value);
	UIElement(Entity* targetEntity, EUIElementType uitype, Color color, int size, Vector2 offset, unsigned short int value);
	~UIElement() override;


private:
	// Inherited via GameObject
	virtual void OnStart() override;
	virtual const bool IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	virtual void Update(const float& _deltatime) override;
	void SetHasSecondBarToRegressBefore(const bool& value) { m_hasASecondBarToRegressBefore = value; } 
	virtual const void FollowPosition(Vector2& newPosition) override;
	virtual void Render() override;

	void RenderProgressBar();
	void RenderRegressBar();
	void UpdateProgressBar();
	void UpdateRegressBar();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::UI; }

};

