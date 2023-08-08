#include "Game.h"

int main()
{
	Game* game = Game::GetInstance();

	game->Run();

	//delete game;

	return 0;
}