#include "MainCharacter.h"
#include "Game.h"


void MainCharacter::OnStart()
{
	Agent::OnStart();
	m_posX = Game::SCREEN_WIDTH / 2;
	m_posY = Game::SCREEN_HEIGHT / 2;
	Weapon* weapon = new Weapon();
	m_weapons.push_back(weapon);
	weapon->OnStart();
}

void MainCharacter::Update()
{
}