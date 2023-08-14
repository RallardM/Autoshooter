#include "Game.h"

int main(void)
{
    Game* game = Game::GetInstance();
    game->StartGame();

    game->CleanUpGame();
    delete game;
    game = nullptr;

    return 0;
}