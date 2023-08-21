#pragma once
#include "raylib.h"
#include "Enumerations.h"

class GameObject
{
	friend class GameObjectPool;
	friend class CollisionManager; // To avoid violation access when CollisionManager tries to access GetGameObjectType()

private:
	static unsigned short int s_gameObjectId;

public:
	unsigned short int m_gameObjectId = 0;

public:
	GameObject();
	virtual ~GameObject() = 0;

private:
	virtual void Update(const float& deltatime) = 0;
	virtual void Render() = 0;
	virtual bool IsActive() const = 0;
	virtual void Reset() = 0;
	virtual const void FollowPosition(Vector2& newPosition);

protected:
	virtual void OnStart() = 0;
	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;

protected:
	Vector2 m_position = { 0.0f, 0.0f };

};