#include "LaserGun.h"

float LaserGun::s_uiOffsetRight = 0.0f;

void LaserGun::Fire()
{
}

void LaserGun::Reset()
{
}

void LaserGun::OnStart()
{
	GameObject::OnStart();
	SetProjectileInfos(SProjectileData());

	Weapon::OnStart();

	m_uiOffset = s_uiOffsetRight;
	s_uiOffsetRight += 5.0f;

	// Add attributes before m_isActive = true;
	m_isActive = true;
}

void LaserGun::Update(float deltatime)
{
}

void LaserGun::Render()
{
	// Add a small offset to the right at every new ExplosiveGun
	Vector2 position = m_position;
	position.x += m_uiOffset;

	// Add a small offsetdown above the explosive gun at the bottom of the player square
	position.y += 25.0f;
	DrawRectangleV(position, m_size, m_color);
}
