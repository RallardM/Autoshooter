#pragma once
#include <list>

#include "Weapon.h"

class MainCharacter : public Agent
{
	friend class Game;

public:
	Color m_color = { 40, 40, 40, 255 };
private:
	std::list<Weapon*> m_weapons;

	// Inherited via Agent
	virtual void OnStart() override;
	virtual void Update() override;
};