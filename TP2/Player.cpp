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
	m_left = m_position.x - (m_width * 0.5f);
	m_top = m_position.y - (m_height * 0.5f);
	m_right = m_left + m_width;
	m_bottom = m_top + m_height;

	// OldBoxCollider
	m_oldLeft = m_left;
	m_oldTop = m_top;
	m_oldRight = m_right;
	m_oldBottom = m_bottom;

	m_isCollide = false;
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
	m_left = m_position.x - (m_width * 0.5f);
	m_top = m_position.y - (m_height * 0.5f);
	m_right = m_left + m_width;
	m_bottom = m_top + m_height;

	// OldBoxCollider
	m_oldLeft = m_left;
	m_oldTop = m_top;
	m_oldRight = m_right;
	m_oldBottom = m_bottom;

	m_isCollide = false;

}

bool Player::Collide(GameObject& gameObject)
{
	if (
		m_left <= gameObject.m_right &&
		m_right >= gameObject.m_left &&
		m_top <= gameObject.m_bottom &&
		m_bottom >= gameObject.m_top
		)
	{
		return true;
	}
	else
	{
		return false;
	}
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
		std::cout << "Fire" << "\n";
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
	m_oldLeft = m_left;
	m_oldTop = m_top;
	m_oldRight = m_right;
	m_oldBottom = m_bottom;

	// Update player position
	m_position.x += m_direction.x * m_speed * deltatime;

	// Update rect
	m_left = floorf(m_position.x - (m_width * 0.5f));
	m_top = floorf(m_position.y - (m_height * 0.5f));
	m_right = m_left + m_width;
	m_bottom = m_top + m_height;

	// Collision Horizontal

	// Update player position
	m_position.y += m_direction.y * m_speed * deltatime;

	// Update rect
	m_left = floorf(m_position.x - (m_width * 0.5f));
	m_top = floorf(m_position.y - (m_height * 0.5f));
	m_right = m_left + m_width;
	m_bottom = m_top + m_height;

	// Collision Vertical
}

void Player::Render()
{
	DrawRectangle(m_left, m_top, m_width, m_height, m_color);
}
