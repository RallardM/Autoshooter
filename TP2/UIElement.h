#pragma once
#include "GameObject.h"

class UIElement : public GameObject
{
	friend class Game;

public:
	UIElement(EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value);
	virtual void OnStart() override;
	void FollowPosition(Vector2 newPosition);

private:
	// Inherited via GameObject
	virtual void Update() override;
	virtual void Render() override;
	void RenderProgressBar();
	void UpdateProgressBar();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::UI; }
	
public:

private:
	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_size = { 32.0f, 32.0f };
	Vector2 m_offset = { 0.0f, 0.0f };
	EUIElementType m_UIType = EUIElementType::COUNT;
	float m_value = 0.0f;

};

