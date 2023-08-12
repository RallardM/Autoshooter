#pragma once
#include "GameObject.h"

class UIElement : public GameObject
{
	friend class Game;

public:
	UIElement(GameObject* targetEntity, EUIElementType uitype, Color color, Vector2 size, Vector2 offset, float value);
	virtual void OnStart() override;
	void FollowPosition(Vector2 newPosition);
	virtual bool IsActive() override { return m_isActive; }
	virtual void Reset() override; // TODO check how to make it private, less spaghetti

private:
	// Inherited via GameObject
	virtual void Update(float deltatime) override;
	virtual void Render() override;
	

	void RenderProgressBar();
	void UpdateProgressBar();
	void UpdateRegressBar();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::UI; }
	
public:

private:
	GameObject* m_targetEntity = nullptr;
	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_size = { 32.0f, 32.0f };
	Vector2 m_offset = { 0.0f, 0.0f };
	EUIElementType m_UIType = EUIElementType::COUNT;
	float m_value = 0.0f;

};

