#include <stdlib.h> 

#include "Projectile.h"
#include "Game.h"
#include <iostream>

//Projectile::Projectile(Vector2 origin, float xSpeed, float ySpeed, float size, float lifetime)
Projectile::Projectile(Vector2 origin, float size, float speed, float lifetime)
{
	m_position = origin;
	m_currentLifetime = lifetime;

	// Calculate the magnitude of the speed vector : squareroot of (x*x + y*y)
	float speedMagnitude = sqrt((speed * speed) + (speed * speed));

	// Generate a random angle
	float randomRadianAngle = static_cast<float>(rand()) / RAND_MAX;
	const float FULL_CIRCLE = 2.0f * PI;
	float randomAngle = FULL_CIRCLE * randomRadianAngle;

	// Calculate new normalized speed values with the same magnitude
	m_xSpeed = speedMagnitude * cos(randomAngle);
	m_ySpeed = speedMagnitude * sin(randomAngle);

	//// Normalize the direction of the projectile
	//m_xSpeed = xSpeed * 2 * rand() / RAND_MAX - xSpeed; //This is not the correct formula
	//m_ySpeed = ySpeed * 2 * rand() / RAND_MAX - ySpeed; //TODO: Change so that the speed is constant


	m_radius = size;
	m_color = WHITE;

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
	//m_position.x = (float)GetScreenWidth() / 2.0f; // TODO
	//m_position.y = (float)GetScreenHeight() / 2.0f;// TODO
}

void Projectile::Update()
{
	m_position.x += m_xSpeed;
	m_position.y += m_ySpeed;
	m_currentLifetime -= GetFrameTime();
	if (m_currentLifetime < 0)
	{
		Game::GetInstance()->UnregisterGameObject(this);
	}
}

void Projectile::Render()
{
	DrawCircleV(m_position, m_radius, m_color);
	// TODO Remi : Vérifier code ajouté par Maurice:
	//DrawRectangle(m_boxCollider->m_left, m_boxCollider->m_top, m_width, m_height, m_color);
}
