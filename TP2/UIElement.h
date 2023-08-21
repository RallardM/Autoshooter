#pragma once
#include "GameObject.h"
#include "Entity.h"

class UIElement : public GameObject
{
	friend class GameObjectPool;
	friend class Player;
	friend class Enemy;

private:
	SUIElementData* m_uiData;
	static unsigned short int s_id;
	bool m_isActive = false;

public:
	unsigned short int m_id = 0;

public:
	UIElement(SUIElementData* m_uiData);
	~UIElement() override;

private:
	// Inherited via GameObject
	virtual void OnStart() override;
	virtual bool IsActive() const override { return m_isActive; }
	virtual void Reset() override;
	virtual void Update(const float& deltatime) override;
	virtual void Render() override;
	virtual const void FollowPosition(Vector2& newPosition) override;

	void RenderProgressBar();
	void RenderRegressBar();
	void UpdateProgressBar();
	void UpdateRegressBar();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::UIELEMENT; }
	void SetUIElementData(SUIElementData* uiData);
};

