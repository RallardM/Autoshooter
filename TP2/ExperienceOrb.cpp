#include "ExperienceOrb.h"
#include "Game.h"

ExperienceOrb::ExperienceOrb(Vector2 origin)
{
	m_position = origin;
}

void ExperienceOrb::OnStart()
{
	GameObject::OnStart();
}

void ExperienceOrb::Update()
{
	Collision();
}

void ExperienceOrb::Render()
{
	DrawCircleGradient((int)m_position.x, (int)m_position.y, m_radius, GREEN, LIGHTGRAY);
}

void ExperienceOrb::Collision()
{
	bool isPlayerCollidingOrb = Game::GetInstance()->AreOrbPlayerColliding(m_position, m_radius);

	if (isPlayerCollidingOrb)
	{
		Game::GetInstance()->UnregisterGameObject(this);
		Game::GetInstance()->AddPlayerExperience(10);
	}
}