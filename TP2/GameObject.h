#pragma once
#include "raylib.h"
#include "Enumerations.h"

class GameObject
{
	friend class GameObjectPool;
	friend class CollisionManager; // To avoid violation access when CollisionManager tries to access GetGameObjectType()

protected: // Protected member variables
	Vector2 m_position = { 0.0f, 0.0f };
	bool m_isActive = false;

protected: // Protected methods
	virtual void OnStart() = 0;

public:  // Public member variables
	unsigned short int m_gameObjectId = 0;

private: // Private member variables
	static unsigned short int s_gameObjectId;

public: // Public methods
	GameObject();
	virtual ~GameObject() = 0;

private: // Private methods
	virtual void Update(const float& deltatime) = 0;
	virtual void Render() = 0;
	virtual const bool IsActive() const = 0;
	virtual void Reset() = 0;
	virtual const void FollowPosition(Vector2& newPosition);

	virtual const Vector2& GetPosition() const = 0;
	virtual const EGameObjectType GetGameObjectType() const = 0;
};