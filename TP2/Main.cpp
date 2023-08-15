#include "Game.h"

int main(void)
{
    Game* game = Game::GetInstance();
    game->StartGame();

    delete game;
    game = nullptr;

    return 0;
}