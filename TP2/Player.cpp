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
#include "GameObjectPool.h"

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
		for (Weapon* weapon : GameObjectPool::GetInstance()->GetActiveWeapons())
		{
			weapon->IncreaseRate();
			weapon->IncreaseProjectileDamage();
			weapon->IncreaseProjectileSize();
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
	if (Game::GetInstance()->IsPaused() && MenuManager::GetInstance()->GetCurrentMenu() == EUIMenuType::LEVELUP_MENU)
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
	m_position.x = (float)Game::GetInstance()->GetMapWidth() * HALF;
	m_position.y = (float)Game::GetInstance()->GetMapHeight() * HALF;

	// Initialize health bar
	SUIElementData healthBarData;
	healthBarData.TARGET = this;
	healthBarData.COLOR = RED;
	healthBarData.BAR_SIZE = PLAYER_HEALTH_BAR_SIZE;
	healthBarData.OFFSET = PLAYER_HEALTH_BAR_OFFSET;
	healthBarData.FLOAT_VALUE = m_health;
	healthBarData.FONT_SIZE = 0;
	healthBarData.UIELEMENT_TYPE = static_cast<unsigned short int>(EUIElementType::REGRESS_BAR);
	healthBarData.INT_VALUE = 0;
	healthBarData.HAS_SECONDARY_BAR = false;
	GameObjectPool::GetInstance()->TakeUIElementFromPool(healthBarData);

	// Initialize experience text
	SUIElementData experienceText;
	experienceText.TARGET = this;
	experienceText.COLOR = GREEN;
	experienceText.BAR_SIZE = PLAYER_EXPERIENCE_BAR_SIZE;
	experienceText.OFFSET = PLAYER_EXPERIENCE_TEXT_OFFSET;
	experienceText.FLOAT_VALUE = 0.0f;
	experienceText.FONT_SIZE = PLAYER_EXPERIENCE_FONT_SIZE;
	experienceText.UIELEMENT_TYPE = static_cast<unsigned short int>(EUIElementType::TEXT);
	experienceText.INT_VALUE = m_totalExperience;
	experienceText.HAS_SECONDARY_BAR = false;
	GameObjectPool::GetInstance()->TakeUIElementFromPool(experienceText);

	// Initialize experience bar
	SUIElementData experienceBar;
	experienceText.TARGET = this;
	experienceText.COLOR = GREEN;
	experienceText.BAR_SIZE = PLAYER_EXPERIENCE_BAR_SIZE;
	experienceText.OFFSET = PLAYER_EXPERIENCE_BAR_OFFSET;
	experienceText.FLOAT_VALUE = 0.0f;
	experienceText.FONT_SIZE = 0;
	experienceText.UIELEMENT_TYPE = static_cast<unsigned short int>(EUIElementType::PROGRESS_BAR);
	experienceText.INT_VALUE = m_experience;
	experienceText.HAS_SECONDARY_BAR = false;
	GameObjectPool::GetInstance()->TakeUIElementFromPool(experienceText);

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
	if (GameObjectPool::GetInstance()->GetPlayerHasSecondaryHealthBar())
	{
		GameObjectPool::GetInstance()->GetPlayerPrimaryHealthBar()->FollowPosition(m_position); // TODO Make pure virtual
	}

	// Update second health bar position
	if (GameObjectPool::GetInstance()->GetPlayerHasSecondaryHealthBar())
	{
		GameObjectPool::GetInstance()->GetPlayerSecondaryHealthBar()->FollowPosition(m_position); // TODO Make pure virtual
	}

	// Update experience text position
	if (GameObjectPool::GetInstance()->GetPlayerExperienceBar() != nullptr)
	{
		GameObjectPool::GetInstance()->GetPlayerExperienceBar()->FollowPosition(m_position); // TODO Make pure virtual
	}

	// Update experience bar position
	if (GameObjectPool::GetInstance()->GetPlayerExperienceBar() != nullptr)
	{
		GameObjectPool::GetInstance()->GetPlayerExperienceBar()->FollowPosition(m_position); // TODO Make pure virtual
	}

	// Update weapon position
	for (Weapon* weapon : GameObjectPool::GetInstance()->GetActiveWeapons())
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

	if (m_health > MAX_HEALTH && GameObjectPool::GetInstance()->GetPlayerHasSecondaryHealthBar())
	{
		// Initialize one additional health bar
		float extraHealth = (float)m_health - (float)MAX_HEALTH;
		// 32.0f  = 100% of the bar
		extraHealth = (extraHealth * PLAYER_EXPERIENCE_BAR_SIZE.x) * HUNDREDTH;
		Vector2 barSize = { extraHealth, PLAYER_EXPERIENCE_BAR_SIZE.y };
		Vector2 offsetFromPlayer = PLAYER_SECOND_HEALTH_BAR_OFFSET; // TODO Remi : make sure the health bonus stops at the full second bar and remove the bonus from the level up menu

		SUIElementData additionalHealthBarData;
		additionalHealthBarData.TARGET = this;
		additionalHealthBarData.COLOR = RED;
		additionalHealthBarData.BAR_SIZE = barSize;
		additionalHealthBarData.OFFSET = offsetFromPlayer;
		additionalHealthBarData.FLOAT_VALUE = m_health;
		additionalHealthBarData.FONT_SIZE = 0;
		additionalHealthBarData.UIELEMENT_TYPE = static_cast<unsigned short int>(EUIElementType::REGRESS_BAR);
		additionalHealthBarData.INT_VALUE = 0;
		additionalHealthBarData.HAS_SECONDARY_BAR = false;
		GameObjectPool::GetInstance()->TakeUIElementFromPool(additionalHealthBarData);
	}
	else if (m_health <= MAX_HEALTH && GameObjectPool::GetInstance()->GetPlayerHasSecondaryHealthBar())
	{
		// Delete additional health bar
		GameObjectPool::GetInstance()->GetPlayerSecondaryHealthBar()->Reset();
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
	for (Weapon* weapon : GameObjectPool::GetInstance()->GetActiveWeapons())
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
	for (Weapon* weapon : GameObjectPool::GetInstance()->GetActiveWeapons())
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
	for (Weapon* weapon : GameObjectPool::GetInstance()->GetActiveWeapons())
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
	GameObjectPool::GetInstance()->TakeHandGunFromPool();
}

void Player::AddNewExplosiveGun()
{
	GameObjectPool::GetInstance()->TakeExplosiveGunFromPool();
}

void Player::AddNewLaserGun()
{
	GameObjectPool::GetInstance()->TakeLaserGunFromPool();
}