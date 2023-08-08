#include "Projectile.h"

Projectile::Projectile(float& x, float& y, float& dx, float& dy)
{
	// Position
	m_position = { x, y };
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


	m_speed = PROJECTILE_SPEED;
	m_lifeTime = 0.0f;


	// BoxCollider
	m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	// OldBoxCollider
	m_oldBoxCollider = m_boxCollider;

	m_isCollide = false;
	m_isDie = false;
}

void Projectile::OnStart()
{
	Game::GetInstance()->RegisterGameObjects(this);
}

void Projectile::Reset(float& x, float& y)
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
	m_isDie = false;

}

void Projectile::Launch()
{
	
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