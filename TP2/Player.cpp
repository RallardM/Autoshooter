#include "Player.h"
#include "Game.h"
#include <iostream>


Player::Player()
{
	// Position
	m_direction = { 0.0f, 0.0f };
	//m_speed = PLAYER_SPEED;

	//// Dimension
	//m_width = PLAYER_WIDTH;
	//m_height = PLAYER_HEIGHT;


	//// BoxCollider
	//m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	//// OldBoxCollider
	//m_oldBoxCollider = m_boxCollider;

	//m_isCollide = false;

	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}

void Player::HandleInput()
{

	if (IsKeyDown(KEY_W))
	{
		//Direction up
		m_direction.y = -1.0f;

	}
	else if (IsKeyDown(KEY_S))
	{
		//Direction down
		m_direction.y = 1.0f;
	}
	else
	{
		m_direction.y = 0.0f;
	}

	if (IsKeyDown(KEY_A))
	{
		//Direction left
		m_direction.x = -1.0f;
	}
	else if (IsKeyDown(KEY_D))
	{
		//Direction right
		m_direction.x = 1.0f;
	}
	else
	{
		m_direction.x = 0.0f;
	}

	//if (IsKeyDown(KEY_SPACE))
	//{
	//	if (!m_weapons.empty())
	//	{
	//		for (int i = 0; i < m_weapons.size(); ++i)
	//		{
	//			m_weapons[i]->Fire();
	//		}
	//	}
	//}

	if (m_direction.x != 0.0f || m_direction.y != 0.0f)
	{
		float magnitude = sqrtf(
			(m_direction.x * m_direction.x) +
			(m_direction.y * m_direction.y)
		);
		m_direction.x /= magnitude;
		m_direction.y /= magnitude;

	}
}

void Player::OnStart()
{
	GameObject::OnStart();
	m_position.x = (float)GetScreenWidth() / 2;
	m_position.y = (float)GetScreenHeight() / 2;
	Weapon* weapon = new Weapon();
	m_weapons.push_back(weapon);
	weapon->OnStart();
}

void Player::Update()
{
	//// Update OldBoxCollider
	//m_oldBoxCollider = m_boxCollider;

	// Update player position
	m_position.x += m_direction.x * PLAYER_SPEED; // *deltatime;

	//// Update body
	//m_boxCollider.Update(m_position.x, m_position.y);

	//// Collision Horizontal
	//Collision();

	// Update player position
	m_position.y += m_direction.y * PLAYER_SPEED; // *deltatime;

	//// Update rect
	//m_boxCollider.Update(m_position.x, m_position.y);

	// Collision Vertical
	//Collision();

	////Set weapon position to follow player position
	//if (!m_weapons.empty())
	//{
	//	for (int i = 0; i < m_weapons.size(); ++i)
	//	{
	//		m_weapons[i]->UpdatePosition(m_position.x, m_position.y);
	//		//m_weapons[i]->Update(deltatime);
	//	}
	//}
}

void Player::Render()
{
	DrawRectangle((int)m_position.x, (int)m_position.y, PLAYER_WIDTH, PLAYER_HEIGHT, m_color);
}
