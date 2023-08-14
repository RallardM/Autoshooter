#include "GameObject.h"
#include "Game.h"

void GameObject::OnStart()
{
	Game::GetInstance()->RegisterGameObject(this);

}