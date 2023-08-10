#include <stdlib.h> 

#include "Projectile.h"
#include "Game.h"

Projectile::Projectile(float xSpeed, float ySpeed, float size, float lifetime)
{
	m_currentLifetime = lifetime;
	m_xSpeed = xSpeed * 2 * rand() / RAND_MAX - xSpeed; //This is not the correct formula
	m_ySpeed = ySpeed * 2 * rand() / RAND_MAX - ySpeed; //TODO: Change so that the speed is constant
	m_radius = size;
	m_color = { 90, 90, 90, 255 };

	float diameter = m_radius * 2;
	// BoxCollider
	//m_boxCollider = BoxCollider(m_position.x, m_position.y, m_width, m_height);
	m_boxCollider = new BoxCollider(m_position.x + m_radius, m_position.y + m_radius, diameter, diameter);
}

Projectile::~Projectile() 
{
	delete m_boxCollider;
}

void Projectile::OnStart()
{
	GameObject::OnStart();
	m_position.x = (float)GetScreenWidth() / 2.0f; // TODO
	m_position.y = (float)GetScreenHeight() / 2.0f;// TODO
}

void Projectile::Update()
{
	m_position.x += m_xSpeed;
	m_position.y += m_ySpeed;
	m_currentLifetime -= GetFrameTime();
	if (m_currentLifetime < 0)
	{
		Game::GetInstance()->UnregisterAgent(this);
	}
}

void Projectile::Render()
{
	DrawCircleV(m_position, m_radius, m_color);
	// TODO Remi : V�rifier code ajout� par Maurice:
	//DrawRectangle(m_boxCollider->m_left, m_boxCollider->m_top, m_width, m_height, m_color);
}
