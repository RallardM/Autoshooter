#include "Weapon.h"


Weapon::Weapon()
	:GameObject()
{
	m_fireMode = FireMode::Auto;
}

Weapon::Weapon(const float& x, const float& y)
	: GameObject(x, y)
{
	m_fireMode = FireMode::Auto;
}

Weapon::Weapon(const float& x, const float& y, const FireMode& fireMode, const bool& isDie)
	: GameObject(x, y, isDie)
{
	m_fireMode = fireMode;
	
}


Weapon::~Weapon()
{}


