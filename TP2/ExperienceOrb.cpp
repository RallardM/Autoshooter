#include <iostream>

#include "ExperienceOrb.h"
#include "Game.h"
#include "CollisionManager.h"

unsigned short int ExperienceOrb::s_id = 0;

ExperienceOrb::ExperienceOrb(Vector2& origin)
{
	m_id = s_id++;
	std::cout << "ExperienceOrb constructor called. ID = " << m_id << std::endl;

	m_position = origin;
}

ExperienceOrb::~ExperienceOrb()
{
	std::cout << "ExperienceOrb destructor called. ID = " << m_id << std::endl;
}

void ExperienceOrb::OnStart()
{
	GameObject::OnStart();

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void ExperienceOrb::Update(float& _deltatime)
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