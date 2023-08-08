#include "Enemy.h"
#include "Weapon.h"

Enemy::Enemy()
{
	
	// Position
	m_position = { 0.0f, 0.0f};

	Spawn();


	m_direction = { 0.0f, 0.0f };
	m_speed = (std::rand() % (int)MIN_ENEMY_SPEED) + MAX_ENEMY_SPEED;

	// Dimension
	m_width = ENEMY_WIDTH;
	m_height = ENEMY_HEIGHT;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);


	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;
	m_isDie = false;

	m_weapons.emplace_back(new Weapon(m_position.x, m_position.y));
}

Enemy::Enemy(float& x, float& y, int& width, int& height)
{
	
	// Position
	m_position = { x, y };
	m_direction = { 0.0f, 0.0f };
	m_speed = (std::rand() % (int)MIN_ENEMY_SPEED) + MAX_ENEMY_SPEED;

	// Dimension
	m_width = width;
	m_height = height;

	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);


	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;
	m_isDie = false;

	m_weapons.emplace_back(new Weapon(m_position.x, m_position.y));
}

Enemy::~Enemy()
{
	/*
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			delete (*it);
		}
	}
	*/
}

void Enemy::OnStart()
{
	Game::GetInstance()->RegisterGameObjects(this);
	if (!m_weapons.empty())
	{
		std::list<Weapon*>::iterator it;
		for (it = m_weapons.begin(); it != m_weapons.end(); it++)
		{
			(*it)->OnStart();
		}

	}
}


void Enemy::Spawn()
{
	int randCorner = std::rand() % 4;
	Vector2 randPosition = { 0.0f, 0.0f };
	
	switch (randCorner)
	{
	case 0:
		// Spawn left
		randPosition.y = std::rand() % HEIGHT;
		randPosition.x = 0;
		break;
	case 1:
		// Spawn top
		randPosition.y = 0;
		randPosition.x = std::rand() % WIDTH;
		break;
	case 2:
		// Spaw right
		randPosition.y = std::rand() % HEIGHT;
		randPosition.x = WIDTH;
		break;
	case 3:
		// Spaw bottom
		randPosition.y = HEIGHT;
		randPosition.x = std::rand() % WIDTH;
		break;
	default:
		break;
	}

	m_position.x = randPosition.x;
	m_position.y = randPosition.y;
}

void Enemy::Track(float& x, float& y)
{
	m_direction.x = x - m_position.x;
	m_direction.y = y - m_position.y;

	float magnitude = sqrtf(
		(m_direction.x * m_direction.x) +
		(m_direction.y * m_direction.y)
	);
	m_direction.x /= magnitude;
	m_direction.y /= magnitude;
}

void Enemy::Update(float deltatime)
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
			//(*it)->Update(deltatime);
		}
	}
}

void Enemy::Render()
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
