#include "Player.h"
#include "ExplosiveGun.h"
#include "Enemy.h"

Player::Player()
	: GameObject()
{
	// Position
	m_direction = { 0.0f, 0.0f };	
	m_speed = PLAYER_SPEED;

	// Dimension
	m_width = PLAYER_WIDTH;
	m_height = PLAYER_HEIGHT;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}

Player::Player(const float& x, const float& y, const bool& isDie)
	: GameObject(x, y, isDie)
{
	// Position
	m_direction = { 0.0f, 0.0f };
	m_speed = PLAYER_SPEED;

	// Dimension
	m_width = PLAYER_WIDTH;
	m_height = PLAYER_HEIGHT;

	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}


Player::Player(const float& x, const float& y, const int& width, const int& height, const bool& isDie)
	: GameObject(x, y, isDie)
{
	// Position
	m_direction = { 0.0f, 0.0f };
	m_speed = PLAYER_SPEED;

	// Dimension
	m_width = width;
	m_height = height;

	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}

Player::~Player()
{}

void Player::OnStart()
{
	Game::GetInstance()->RegisterGameObjects(this);
	if (!m_weapons.empty())
	{
		for (int i = 0; i < m_weapons.size(); ++i)
		{
			m_weapons[i]->OnStart();
		}
	}
}

void Player::Collision(const std::string& direction)
{
	//std::vector<Enemy*> collision_Enemies;
	
	if (!Game::GetInstance()->m_gameObjectsEnemies.empty())
    {
        for (int i = 0; i != Game::GetInstance()->m_gameObjectsEnemies.size(); ++i)
        {
			Game::GetInstance()->m_gameObjectsEnemies[i]->m_isCollide = Game::GetInstance()->m_gameObjectsEnemies[i]->m_boxCollider.Collide(m_boxCollider);
			if (Game::GetInstance()->m_gameObjectsEnemies[i]->m_isCollide && !Game::GetInstance()->m_gameObjectsEnemies[i]->m_isDie)
			{
				Game::GetInstance()->m_gameObjectsEnemies[i]->m_isDie = true;
				Game::GetInstance()->m_gameObjectsEnemies[i]->Spawn();
			}
			else if (Game::GetInstance()->m_gameObjectsEnemies[i]->m_isDie)
			{
				Game::GetInstance()->m_gameObjectsEnemies[i]->m_isDie = false;
			}
        }
    }
	
	
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

	if (IsKeyDown(KEY_SPACE))
	{
		if (!m_weapons.empty())
		{
			for (int i = 0; i < m_weapons.size(); ++i)
			{
				m_weapons[i]->Fire();
			}
		}
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

void Player::Update(float deltatime)
{
	// Update OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	// Update player position
	m_position.x += m_direction.x * m_speed * deltatime;

	// Update body
	m_boxCollider.Update(m_position.x, m_position.y);
	
	// Collision Horizontal
	Collision();

	// Update player position
	m_position.y += m_direction.y * m_speed * deltatime;

	// Update rect
	m_boxCollider.Update(m_position.x, m_position.y);

	// Collision Vertical
	Collision();

	//Set weapon position to follow player position
	if (!m_weapons.empty())
	{
		for (int i = 0; i < m_weapons.size(); ++i)
		{
			m_weapons[i]->UpdatePosition(m_position.x, m_position.y);
			//m_weapons[i]->Update(deltatime);
		}
	}
	
}

void Player::Render()
{
	/*
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			(*it)->Render();
		}
	}
	*/
	DrawRectangle(m_boxCollider.m_left, m_boxCollider.m_top, m_width, m_height, m_color);
}
