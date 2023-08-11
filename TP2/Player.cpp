#include "Player.h"
#include "Game.h"
#include "HandGun.h"

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
	// TODO Remi : Vérifier centre de la map au lieu de centre de l'ecran
	//m_position.x = (float)GetScreenWidth() / 2;
	//m_position.y = (float)GetScreenHeight() / 2;
	m_position.x = (float)Game::GetMapWidth() / 2;
	m_position.y = (float)Game::GetMapHeight() / 2;	

	//m_position.x = (float)GetMapWidth() / 2;
	//m_position.y = (float)GetMapHeight() / 2;
	HandGun* weapon = new HandGun();
	m_weapons.push_back(weapon);
	weapon->OnStart();
}

void Player::Update()
{
	// TODO Remi : Vérifier code ajouté par Maurice:
	//// Update OldBoxCollider
	//m_oldBoxCollider = m_boxCollider;

	// Update player position
	m_position.x += m_direction.x * PLAYER_SPEED; // *deltatime;

	// TODO Remi : Vérifier code ajouté par Maurice:
	//// Update body
	//m_boxCollider.Update(m_position.x, m_position.y);

	//// Collision Horizontal
	//Collision();

	// Update player position
	m_position.y += m_direction.y * PLAYER_SPEED; // *deltatime;

	// TODO Remi : Vérifier code ajouté par Maurice:
	//// Update rect
	//m_boxCollider.Update(m_position.x, m_position.y);

	// Collision Vertical
	//Collision();

	//Set weapon position to follow player position

	// TODO Remi : demander a Maurice pourquoi un vecteur au lieu de la liste initiale
	//if (!m_weapons.empty()) 
	//{
	//	for (int i = 0; i < m_weapons.size(); ++i)
	//	{
	//		m_weapons[i]->FollowPosition(m_position);
	//		//m_weapons[i]->Update(deltatime);
	//	}
	//}

	//if (!m_weapons.empty())
	//{
	//	for (int i = 0; i < m_weapons.size(); ++i)
	//	{
	//		m_weapons[i]->FollowPosition(m_position);
	//		//m_weapons[i]->Update(deltatime);
	//	}
	//}

	for (Weapon* weapon : m_weapons)
	{
		if (weapon == nullptr)
		{
			continue;
		}

		weapon->FollowPosition(m_position);
	}

	// Update camera position to player position
	Game::UpdateCameraPosition(m_position);
}

void Player::Render()
{
	DrawRectangleV(m_position, m_playerSize, m_color);
}
