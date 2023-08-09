#include "GameObject.h"
#include "Game.h"

void GameObject::OnStart()
{
	Game::GetInstance()->RegisterAgent(this);
}
