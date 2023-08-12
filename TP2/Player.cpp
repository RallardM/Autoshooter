#include "Player.h"
#include "Game.h"
#include "HandGun.h"
#include <iostream>

Player::~Player()
{
	// Empty weapon list
	for (auto it = m_weapons.begin(); it != m_weapons.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}

	m_weapons.clear();

	// Delete health bar
	delete m_healthBar;
	m_healthBar = nullptr;

	// Delete experience bar
	delete m_experienceBar;
	m_experienceBar = nullptr;
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

	m_position.x = (float)Game::GetInstance()->GetMapWidth() / 2;
	m_position.y = (float)Game::GetInstance()->GetMapHeight() / 2;

	// Initialize health bar
	Vector2 barSize = { 32.0f, 3.0f };
	Vector2 offsetFromPlayer = { 0.0f, 33.0f };
	m_healthBar = new UIElement(this, EUIElementType::REGRESS_BAR, RED, barSize, offsetFromPlayer, m_health);
	m_healthBar->OnStart();

	// Initialize experience bar
	barSize = { 32.0f, 3.0f };
	offsetFromPlayer = { 0.0f, 36.0f };
	m_experienceBar = new UIElement(this, EUIElementType::PROGRESS_BAR, GREEN, barSize, offsetFromPlayer, m_experience);
	m_experienceBar->OnStart();

	HandGun* handGun = new HandGun();
	m_weapons.push_back(handGun);
	handGun->OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void Player::Update(float deltatime)
{
	VerifyHealth();
	VerifyExperience();

	// Update player position
	m_position.x += m_direction.x * PLAYER_SPEED * deltatime;
	m_position.y += m_direction.y * PLAYER_SPEED * deltatime;

	// Update health bar position
	if (m_healthBar != nullptr)
	{
		m_healthBar->FollowPosition(m_position); // TODO Make pure virtual
	}
	
	// Update experrience bar position
	if (m_experienceBar != nullptr)
	{
		m_experienceBar->FollowPosition(m_position); // TODO Make pure virtual
	}

	// Update weapon position
	for (Weapon* weapon : m_weapons)
	{
		if (weapon == nullptr)
		{
			continue;
		}

		weapon->FollowPosition(m_position);// TODO Make pure virtual
	}

	// Update camera position to player position
	Game::GetInstance()->UpdateCameraPosition(m_position);

	Collision();
}

void Player::Render()
{
	DrawRectangleV(m_position, m_playerSize, m_color);
}

void Player::Reset()
{

	// Reset everything before m_isActive = false; in GameObject::Reset();
	GameObject::Reset();
}

void Player::Collision()
{
	Rectangle playerRect = { m_position.x, m_position.y, m_playerSize.x, m_playerSize.y };
	bool isEnemyHitByProjctile = Game::GetInstance()->ArePlayerEnemyColliding(playerRect);

	if (isEnemyHitByProjctile)
	{
		m_health -= 10;
	}
}

void Player::VerifyHealth()
{
	if (m_health <= 0)
	{
		//TODO: Game Over screen or info
	}
}

void Player::VerifyExperience()
{
	if (m_experience >= 100)
	{
		m_experience = 0;
		m_level++;
	}
}