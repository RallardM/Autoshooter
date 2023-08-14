#pragma once
#include "raylib.h"
#include "Enumerations.h"

class GameObject
{
	friend class Game;

protected:
	Vector2 m_position = { 0.0f, 0.0f };
	bool m_isActive = false;
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;
	
public:
	virtual void OnStart() = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Render() = 0;
	virtual const bool IsActive() const = 0;
	virtual void Reset() = 0;

};