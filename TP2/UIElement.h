#pragma once
#include "GameObject.h"
#include "Entity.h"

class UIElement : public GameObject
{
	friend class GameObjectPool;
	friend class Player;
	friend class Enemy;

private:
	//Entity* m_targetEntity = nullptr;
	//Color m_color = { 40, 40, 40, 255 };
	//Vector2 m_size = { 32.0f, 32.0f };
	//Vector2 m_offset = { 0.0f, 0.0f };
	//EUIElementType m_UIType = EUIElementType::COUNT;
	//float m_floatValue = 0.0f;
	//unsigned short int m_intValue = 0;
	//int m_fontSize = 0;
	SUIElementData& m_uiData;
	static unsigned short int s_id;

public:
	unsigned short int m_id = 0;

public:
	UIElement(SUIElementData& m_uiData);
	~UIElement() override;

private:
	// Inherited via GameObject
	virtual void OnStart() override;
	void FollowPosition(const Vector2& newPosition);
	virtual const bool IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;

	void RenderProgressBar();
	void RenderRegressBar();
	void UpdateProgressBar();
	void UpdateRegressBar();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::UIELEMENT; }
	void SetUIElementData(SUIElementData& uiData) { m_uiData = uiData; }

};

