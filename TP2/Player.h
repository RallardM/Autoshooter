#pragma once
#include <list>

#include "Weapon.h"

class Player : public GameObject
{
	friend class Game;

public:
	Player();
	
private:
	// Player default parameter
	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGHT = 32;
	const float PLAYER_SPEED = 25.0f;

	Color m_color = { 40, 40, 40, 255 };
	Vector2 m_direction = { 0.0f, 0.0f };

	std::list<Weapon*> m_weapons;

	void HandleInput();

	// Inherited via GameObject
	virtual void OnStart() override;
	virtual void Update() override;
	virtual void Render() override;
};