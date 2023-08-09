#include "Enemy.h"
#include "Weapon.h"

Enemy::Enemy()
	: GameObject()
{
	// Position
	Spawn();
	m_direction = { 0.0f, 0.0f };
	m_speed = MIN_ENEMY_SPEED;


	// Dimension
	m_width = ENEMY_WIDTH;
	m_height = ENEMY_HEIGHT;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}

Enemy::Enemy(const float& x, const float& y, const bool& isDie)
	: GameObject(x, y, isDie)
{
	// Position
	Spawn();
	m_direction = { 0.0f, 0.0f };
	m_speed = MIN_ENEMY_SPEED;

	// Dimension
	m_width = ENEMY_WIDTH;
	m_height = ENEMY_HEIGHT;

	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}

Enemy::Enemy(const float& x, const float& y, const int& width, const int& height, const bool& isDie)
	: GameObject(x, y, isDie)
{
	// Position
	Spawn();
	m_direction = { 0.0f, 0.0f };
	m_speed = MIN_ENEMY_SPEED;

	// Dimension
	m_width = ENEMY_WIDTH;
	m_height = ENEMY_HEIGHT;

	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;

	//m_weapons.emplace_back(new ExplosiveGun(m_position.x, m_position.y));
}


Enemy::~Enemy()
{}

void Enemy::OnStart()
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


void Enemy::Spawn()
{
	int randCorner = std::rand() % 4;
	m_speed = std::rand() % (int)(MAX_ENEMY_SPEED - MIN_ENEMY_SPEED) + MAX_ENEMY_SPEED;
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
		for (int i = 0; i < m_weapons.size(); ++i)
		{
			m_weapons[i]->UpdatePosition(m_position.x, m_position.y);
			//m_weapons[i]->Update(deltatime);
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
