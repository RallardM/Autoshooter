#include "Player.h"


Player::Player()
{
	// Position
	m_position = { SCREEN_CENTER_POINT.x, SCREEN_CENTER_POINT.y };
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

	m_weapons.emplace_back(new Weapon(m_position.x, m_position.y));
}

Player::Player(float& x, float& y, int& width, int& height)
{
	// Position
	m_position = { x, y };
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

	m_weapons.emplace_back(new Weapon(m_position.x, m_position.y));
}

Player::~Player()
{
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			delete (*it);
		}
	}
}

bool Player::Collide(GameObject& gameObject)
{
	return false; 
}

void Player::OnStart()
{
	
	//m_weapons.push_back(weapon);
	//weapon->OnStart();
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
			std::list<Weapon*>::iterator it;
			for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
			{
				(*it)->Fire();
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

	// Update player position
	m_position.y += m_direction.y * m_speed * deltatime;

	// Update rect
	m_boxCollider.Update(m_position.x, m_position.y);

	// Collision Vertical

	//Set weapon position to follow player position
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			(*it)->UpdatePosition(m_position.x, m_position.y);
			(*it)->Update(deltatime);
		}
	}
}

void Player::Render()
{
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			(*it)->Render();
		}
	}
	DrawRectangle(m_boxCollider.m_left, m_boxCollider.m_top, m_width, m_height, m_color);
}
