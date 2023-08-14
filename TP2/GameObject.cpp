#include "GameObject.h"
#include "Game.h"

unsigned short int GameObject::s_gameObjectId = 0;

void GameObject::OnStart()
{
	m_gameObjectId = s_gameObjectId++;
	Game::GetInstance()->RegisterGameObject(this);

}