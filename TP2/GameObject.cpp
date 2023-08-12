#include "GameObject.h"
#include "Game.h"

void GameObject::OnStart()
{
	Game::GetInstance()->RegisterGameObject(this);
}

void GameObject::Reset()
{
	m_isActive = false;
}