#include "ExperienceOrb.h"
#include "Game.h"
#include "CollisionManager.h"

ExperienceOrb::ExperienceOrb(Vector2 origin)
{
	m_position = origin;
}

void ExperienceOrb::OnStart()
{
	GameObject::OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void ExperienceOrb::Update(float _deltatime)
{
	if (!m_isActive)
	{
		return;
	}

	Collision();
}

void ExperienceOrb::Render()
{
	DrawCircleGradient((int)m_position.x, (int)m_position.y, m_radius, GREEN, LIGHTGRAY);
}

void ExperienceOrb::Reset()
{

	// Reset everything before m_isActive = false;
	m_isActive = false;
}

void ExperienceOrb::Collision()
{
	bool isPlayerCollidingOrb = CollisionManager::GetInstance()->AreOrbPlayerColliding(m_position, m_radius);

	if (isPlayerCollidingOrb)
	{
		Game::GetInstance()->AddPlayerExperience(10);
		Reset();
		Game::GetInstance()->UnregisterGameObject(this);
	}
}