#include "Game.h"
#include "GameObjectPool.h"

int main(void)
{
    Game* game = Game::GetInstance();
    GameObjectPool::GetInstance()->InitializeGameObjects();
    game->MainLoop();

    delete game;
    game = nullptr;

    return 0;
}