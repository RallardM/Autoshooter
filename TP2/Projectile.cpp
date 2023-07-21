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
}

void Projectile::OnStart()
{
	Agent::OnStart();
	m_posX = Game::SCREEN_WIDTH / 2.0f;
	m_posY = Game::SCREEN_HEIGHT / 2.0f;
}

void Projectile::Update()
{
	m_posX += m_xSpeed;
	m_posY += m_ySpeed;
	m_currentLifetime -= GetFrameTime();
	if (m_currentLifetime < 0)
	{
		Game::GetInstance()->UnregisterAgent(this);
	}
}
