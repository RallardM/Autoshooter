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
	m_left = m_position.x;
	m_top = m_position.y;
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
	m_left = m_position.x;
	m_top = m_position.y;
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

void Player::Update(float deltatime)
{

}

void Player::Render()
{
	BeginDrawing();

	ClearBackground(DARKGRAY);
	DrawRectangle(m_position.x, m_position.y, m_width, m_height, m_color);

	EndDrawing();
}
