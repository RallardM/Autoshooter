#pragma once
#include <list>
#include "Weapon.h"

class Player : public GameObject
{
	friend class Game;

public:
	Player();
	virtual const Vector2& GetPosition() const override { return m_position; }
	virtual const EGameObjectType GetGameObjectType() const override { return EGameObjectType::PLAYER; }
	
private:
	// Player default parameter
	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_playerSize = { 32.0f, 32.0f };
	Vector2 m_direction = { 0.0f, 0.0f };
	//EGameObjectType m_gameObjectType;

	const float PLAYER_SPEED = 10.0f;


	std::list<Weapon*> m_weapons;

	void HandleInput();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
	
};