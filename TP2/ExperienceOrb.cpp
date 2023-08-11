#include "ExperienceOrb.h"

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
}

void ExperienceOrb::Render()
{
	DrawCircleGradient(m_position.x, m_position.y, m_radius, GREEN, LIGHTGRAY);
}
