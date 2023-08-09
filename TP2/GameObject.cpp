#include "GameObject.h"

GameObject::GameObject()
{
	m_position = { SCREEN_CENTER_POINT.x, SCREEN_CENTER_POINT.y };
	m_isDie = false;
}

GameObject::GameObject(const float& x, const float& y)
{
	m_position.x = x;
	m_position.y = y;
	m_isDie = false;
}

GameObject::GameObject(const float& x, const float& y, const bool& isDie)
{
	m_position.x = x;
	m_position.y = y;
	m_isDie = isDie;
}

GameObject::~GameObject()
{}