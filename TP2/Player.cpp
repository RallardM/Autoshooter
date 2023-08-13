#include "Player.h"
#include "Game.h"
#include "HandGun.h"
#include "MathUtils.h"
#include "Weapon.h"
#include <iostream>

Player::~Player()
{
	// TODO debug crashes when esc
	// 
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

	// Delete second health bar
	delete m_secondHealthBar;
	m_secondHealthBar = nullptr;

	// Delete experience bar
	delete m_experienceBar;
	m_experienceBar = nullptr;
}

void Player::HandleInput()
{
	// Debug keys

	if (IsKeyPressed(KEY_F1))
	{
		Game::GetInstance()->PauseGame();
	}

	// Experience Menu Keys
	if (Game::GetInstance()->IsPaused())
	{
		if (IsKeyPressed(KEY_ONE))
		{
			// Increase shooting rate
			IncreaseWeaponRate();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_TWO))
		{
			// Increase projectile damages
			IncreaseProjectileDamage();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_THREE))
		{
			// Increase projectile size
			IncreaseProjectileSize();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_FOUR))
		{
			// Increase health capacity
			IncreaseHealth();
			Game::GetInstance()->PauseGame();
		}

		return;
	}

	// Movement keys

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

	m_position.x = (float)Game::GetInstance()->GetMapWidth() * HALF;
	m_position.y = (float)Game::GetInstance()->GetMapHeight() * HALF;

	// Initialize health bar
	Vector2 barSize = { 32.0f, 3.0f };
	Vector2 offsetFromPlayer = { 0.0f, 33.0f };
	m_healthBar = new UIElement(this, EUIElementType::REGRESS_BAR, RED, barSize, offsetFromPlayer, m_health);
	m_healthBar->OnStart();

	// Initialize experience text
	int fontSize = 15;
	offsetFromPlayer = { 3.0f, 8.0f }; // { 0.0f, 33.0f };
	m_experienceText = new UIElement(this, EUIElementType::TEXT, GREEN, fontSize, offsetFromPlayer, m_totalExperience);
	m_experienceText->OnStart();

	// Initialize experience bar
	barSize = { 32.0f, 3.0f };
	offsetFromPlayer = { 0.0f, -3.0f };
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

	// Update second health bar position
	if (m_secondHealthBar != nullptr)
	{
		m_secondHealthBar->FollowPosition(m_position); // TODO Make pure virtual
	}

	// Update experience text position
	if (m_experienceText != nullptr)
	{
		m_experienceText->FollowPosition(m_position); // TODO Make pure virtual
	}
	
	// Update experience bar position
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

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void Player::Collision()
{
	Rectangle playerRect = { m_position.x, m_position.y, m_playerSize.x, m_playerSize.y };
	bool isEnemyHitPlayer = Game::GetInstance()->ArePlayerEnemyColliding(playerRect);

	if (isEnemyHitPlayer)
	{
		//m_health -= 10;
	}
}

void Player::VerifyHealth()
{
	if (m_health <= 0)
	{
		//TODO: Game Over screen or info delete ui pointers 
	}

	if (m_health > MAX_HEALTH && m_secondHealthBar == nullptr)
	{
		// Initialize one additional health bar
		float extraHealth = (float)m_health - (float)MAX_HEALTH;
		// 32.0f  = 100% of the bar
		extraHealth = (extraHealth * 32.0f) / 100;
		Vector2 barSize = { extraHealth, 3.0f };
		Vector2 offsetFromPlayer = { 0.0f, 37.0f };
		m_secondHealthBar = new UIElement(this, EUIElementType::REGRESS_BAR, RED, barSize, offsetFromPlayer, m_health);
		m_secondHealthBar->OnStart();
		m_healthBar->SetHasSecondBarToRegressBefore(true);
	}
	else if (m_health <= MAX_HEALTH && m_secondHealthBar != nullptr)
	{
		// Delete additional health bar
		delete m_secondHealthBar;
		m_secondHealthBar = nullptr;
		m_healthBar->SetHasSecondBarToRegressBefore(false);
	}
}

void Player::VerifyExperience()
{
	if (m_experience >= 100)
	{
		m_experience = 0;
		m_level++;
		Game::GetInstance()->PauseGame();
	}
}

void Player::IncreaseWeaponRate()
{
	for (Weapon* weapon : m_weapons)
	{
		if (weapon == nullptr)
		{
			continue;
		}

		weapon->IncreaseRate();
	}
}

void Player::IncreaseProjectileDamage()
{
	for (Weapon* weapon : m_weapons)
	{
		if (weapon == nullptr)
		{
			continue;
		}

		weapon->IncreaseProjectileDamage();
	}
}

void Player::IncreaseProjectileSize()
{
	for (Weapon* weapon : m_weapons)
	{
		if (weapon == nullptr)
		{
			continue;
		}

		weapon->IncreaseProjectileSize();
	}
}

void Player::IncreaseHealth()
{
	m_health += 10;
}
