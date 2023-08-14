#include "Game.h"

int main(void)
{
    Game* game = Game::GetInstance();
    game->StartGame();

    game->CleanUpGame(); // TODO verify if it is propelry cleaning
    delete game;
    game = nullptr;

    return 0;
}