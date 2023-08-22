#include <iostream>

#include "Player.h"
#include "Game.h"
#include "HandGun.h"
#include "ExplosiveGun.h"
#include "LaserGun.h"
#include "MathUtils.h"
#include "Weapon.h"
#include "MenuManager.h"
#include "CollisionManager.h"

Player::Player()
{
	std::cout << "Player constructor" << std::endl;
}

Player::~Player()
{
	std::cout << "Player destructor" << std::endl;
}

void Player::HandleInput()
{
	// Debug keys

	// Debug Level Up Menu
	if (IsKeyPressed(KEY_F1))
	{
		Game::GetInstance()->PauseGame();
		MenuManager::GetInstance()->SetCurrentMenu(EUIMenuType::LEVELUP_MENU);
	}

	// Debug Game Over Menu
	if (IsKeyPressed(KEY_F2))
	{
		Game::GetInstance()->PauseGame();
		MenuManager::GetInstance()->SetCurrentMenu(EUIMenuType::GAMEOVER_MENU);
	}

	// Debug + 5 Levels
	if (IsKeyPressed(KEY_F5))
	{
		m_level += FIVE_LEVELS_DEBUG;
		for (Weapon* in : m_weapons)
		{
			in->IncreaseRate();
			in->IncreaseProjectileDamage();
			in->IncreaseProjectileSize();
		}
		IncreaseHealth();
		IncreaseHealth();
	}
	
	// Main menu
	if (Game::GetInstance()->IsPaused() && MenuManager::GetInstance()->GetCurrentMenu() == EUIMenuType::MAIN_MENU)
	{
		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER))
		{
			MenuManager::GetInstance()->SetCurrentMenu(EUIMenuType::LEVELUP_MENU);
			Game::GetInstance()->PauseGame();
		}
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
			// Increase enemy damages
			IncreaseProjectileDamage();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_THREE))
		{
			// Increase enemy size
			IncreaseProjectileSize();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_FOUR))
		{
			// Increase health capacity
			IncreaseHealth();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_FIVE))
		{
			// Add new HandGun
			AddNewHandGun();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_SIX))
		{
			// Add new Explosive Gun
			AddNewExplosiveGun();
			Game::GetInstance()->PauseGame();
		}
		else if (IsKeyPressed(KEY_SEVEN))
		{
			// Add new Laser Gun
			AddNewLaserGun();
			Game::GetInstance()->PauseGame();
		}

		return;
	}

	// Movement keys

	if (IsKeyDown(KEY_W))
	{
		//Direction up
		m_direction.y = UP.y;

	}
	else if (IsKeyDown(KEY_S))
	{
		//Direction down
		m_direction.y = DOWN.y;
	}
	else
	{
		m_direction.y = NO_DIRECTION.y;
	}

	if (IsKeyDown(KEY_A))
	{
		//Direction left
		m_direction.x = LEFT.x;
	}
	else if (IsKeyDown(KEY_D))
	{
		//Direction right
		m_direction.x = RIGHT.x;
	}
	else
	{
		m_direction.x = NO_DIRECTION.x;
	}

	// If player is moving diagonally, normalize the direction vector
	if (m_direction.x != NO_DIRECTION.x || m_direction.y != NO_DIRECTION.y)
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
	Vector2 barSize = PLAYER_HEALTH_BAR_SIZE;
	Vector2 offsetFromPlayer = PLAYER_HEALTH_BAR_OFFSET;
	m_healthBar = new UIElement(this, EUIElementType::REGRESS_BAR, RED, barSize, offsetFromPlayer, m_health);
	m_healthBar->OnStart();

	// Initialize experience text
	int fontSize = PLAYER_EXPERIENCE_FONT_SIZE;
	offsetFromPlayer = PLAYER_EXPERIENCE_TEXT_OFFSET;
	m_experienceText = new UIElement(this, EUIElementType::TEXT, GREEN, fontSize, offsetFromPlayer, m_totalExperience);
	m_experienceText->OnStart();

	// Initialize experience bar
	barSize = PLAYER_EXPERIENCE_BAR_SIZE;
	offsetFromPlayer = PLAYER_EXPERIENCE_BAR_OFFSET;
	m_experienceBar = new UIElement(this, EUIElementType::PROGRESS_BAR, GREEN, barSize, offsetFromPlayer, m_experience);
	m_experienceBar->OnStart();

	AddNewHandGun();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void Player::Update(const float& deltatime)
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
	CameraManager::GetInstance()->UpdateCameraPosition(m_position);

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
	bool isEnemyHitPlayer = CollisionManager::GetInstance()->ArePlayerEnemyColliding(playerRect);

	if (!isEnemyHitPlayer)
	{
		return;
	}

	Enemy* enemy = CollisionManager::GetInstance()->GetCollidingEnemy(playerRect);

	if (enemy == nullptr)
	{
		return;
	}

	if (enemy->m_id == m_previousEnemyId)
	{
		return;
	}

	m_previousEnemyId = enemy->m_id;

	m_health -= ENEMY_DAMAGE;
}

void Player::VerifyHealth()
{
	if (m_health <= 0)
	{
		Game::GetInstance()->PauseGame();
		MenuManager::GetInstance()->SetCurrentMenu(EUIMenuType::GAMEOVER_MENU);
	}

	if (m_health > MAX_HEALTH && m_secondHealthBar == nullptr)
	{
		// Initialize one additional health bar
		float extraHealth = (float)m_health - (float)MAX_HEALTH;
		// 32.0f  = 100% of the bar
		extraHealth = (extraHealth * PLAYER_EXPERIENCE_BAR_SIZE.x) * HUNDREDTH;
		Vector2 barSize = { extraHealth, PLAYER_EXPERIENCE_BAR_SIZE.y };
		Vector2 offsetFromPlayer = PLAYER_SECOND_HEALTH_BAR_OFFSET; // TODO Remi : make sure the health bonus stops at the full second bar and remove the bonus from the level up menu
		m_secondHealthBar = new UIElement(this, EUIElementType::REGRESS_BAR, RED, barSize, offsetFromPlayer, m_health);
		m_secondHealthBar->OnStart();
		bool hasSecondBarToRegressBefore = true;
		m_healthBar->SetHasSecondBarToRegressBefore(hasSecondBarToRegressBefore);
	}
	else if (m_health <= MAX_HEALTH && m_secondHealthBar != nullptr)
	{
		// Delete additional health bar
		delete m_secondHealthBar;
		m_secondHealthBar = nullptr;
		bool hasSecondBarToRegressBefore = false;
		m_healthBar->SetHasSecondBarToRegressBefore(hasSecondBarToRegressBefore);
	}
}

void Player::VerifyExperience()
{
	// TODO Remi : create a higher number of experience to reach for every new level
	// If a hundred experience is reached, the player levels up
	if (m_experience >= 100)
	{
		m_experience = 0;
		m_level++;
		Game::GetInstance()->PauseGame();
		MenuManager::GetInstance()->SetCurrentMenu(EUIMenuType::LEVELUP_MENU);
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

		// TODO Remi : make sure the rate bonus stops on individual projectiles before they 
		// becomes too chaotic and remove the bonus from the level up menu if all weapon 
		// has reach the max rate but re-add if a new weapon is not at its fastest rate
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

		// TODO Remi : make sure the size bonus stops on individual projectiles before they 
		// becomes too chaotic and remove the bonus from the level up menu if all weapon 
		// has reach the max size but re-add  if a new weapon is not at its largest size
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
	// TODO Remi : make sure the health bonus stops at the 
	// full second bar and remove the bonus from the level up menu
	m_health += TEN_HEALTH_POINTS_BONUS;
}

void Player::AddNewHandGun()
{
	HandGun* handGun = new HandGun();
	m_weapons.push_back(handGun);
	handGun->OnStart();
}

void Player::AddNewExplosiveGun()
{
	ExplosiveGun* explosiveGun = new ExplosiveGun();
	m_weapons.push_back(explosiveGun);
	explosiveGun->OnStart();
}

void Player::AddNewLaserGun()
{
	LaserGun* laserGun = new LaserGun();
	m_weapons.push_back(laserGun);
	laserGun->OnStart();
}