#include "Projectile.h"

Projectile::Projectile()
	: GameObject()
{
	m_originPosition = { 0.0f, 0.0f };// Use to memorise the intial position of the projectile when is generate before being translate to the center use to reset position of projectile to player position
	m_initDirection = { 0.0f, 0.0f };// Use to set the initial direction when the projectile is generate
	m_direction = { 0.0f, 0.0f };// Use to set the direction of the projectile 
	m_speed = PROJECTILE_SPEED;// Projectile speed
	m_lifeTime = 0.0f;// Life time before projectile is destroy if is not touch any obstacle

	// Dimension
	m_width = PROJECTILE_WIDTH;
	m_height = PROJECTILE_HEIGHT;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;


	m_color = RED;
	m_isCollide = false;
	m_isDie = true;
}

Projectile::Projectile( const float& x, const float& y, const float& dx, const float& dy)
	:GameObject(x, y, true)
{
	// Position
	m_originPosition = { dx, dy };
	m_initDirection = { dx, dy };
	m_direction = { 0.0f, 0.0f };

	// Normalize the direction of the projectile
	float magnitude = sqrtf(
		(m_initDirection.x * m_initDirection.x) +
		(m_initDirection.y * m_initDirection.y)
	);
	m_initDirection.x /= magnitude;
	m_initDirection.y /= magnitude;

	m_width = PROJECTILE_WIDTH;
	m_height = PROJECTILE_HEIGHT;

	m_speed = PROJECTILE_SPEED;
	m_lifeTime = 0.0f;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;
}

Projectile::Projectile( const float& x, const float& y, const float& dx, const float& dy, const int& width, const int& height, const bool& isDie)
	: GameObject(x, y, isDie)
{
	// Position
	m_originPosition = {dx, dy};
	m_initDirection = { dx, dy };
	m_direction = {0.0f, 0.0f};

	// Normalize the direction of the projectile
	float magnitude = sqrtf(
		(m_initDirection.x * m_initDirection.x) +
		(m_initDirection.y * m_initDirection.y)
	);
	m_initDirection.x /= magnitude;
	m_initDirection.y /= magnitude;

	m_width = width;
	m_height = height;

	m_speed = PROJECTILE_SPEED;
	m_lifeTime = 0.0f;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;
}

Projectile::~Projectile()
{}

void Projectile::OnStart()
{
	Game::GetInstance()->RegisterGameObjects(this);
}

void Projectile::Reload(float& x, float& y)
{
	// Position
	m_position = { (m_originPosition.x + x), (m_originPosition.y + y) };
	m_direction = {0.0f, 0.0f};
	m_speed = PROJECTILE_SPEED;
	m_lifeTime = 0.0f;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;
	m_isDie = true;

}

void Projectile::Fire()
{
	m_isDie = false;
	m_direction.x = m_initDirection.x;
	m_direction.y = m_initDirection.y;
}

void Projectile::Update(float deltatime)
{
	m_lifeTime += deltatime;

	if (m_lifeTime >= 2.0f)
	{
		m_isDie = true;
	}

	// Update old box collider
	m_oldBoxCollider = m_boxCollider;

	// Update position x
	m_position.x += m_direction.x * m_speed * deltatime;

	// Update box collider
	m_boxCollider.Update(m_position.x, m_position.y);

	// Check Collision horizontal

	// Update position y
	m_position.y += m_direction.y * m_speed * deltatime;

	// Update box collider
	m_boxCollider.Update(m_position.x, m_position.y);

	// Check collision Vertical
}

void Projectile::Render()
{
	DrawRectangle(m_boxCollider.m_left, m_boxCollider.m_top, m_width, m_height, m_color);
}