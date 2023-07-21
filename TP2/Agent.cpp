#include "Agent.h"
#include "Game.h"

void Agent::OnStart()
{
	Game::GetInstance()->RegisterAgent(this);
}
