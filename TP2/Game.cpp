#include <iostream>

#include "Game.h"
#include "MainCharacter.h"
#include "Agent.h"
#include "Projectile.h"

using namespace std;

Game* Game::_Instance = 0;

int main(void)
{
    Game* game = new Game();
    game->StartGame();

    return 0;
}

void Game::StartGame()
{
    _Instance = this;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(60);

    m_mainCharacter = new MainCharacter();
    m_mainCharacter->OnStart();
    MainLoop();
}

void Game::MainLoop()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawRectangle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, 20, m_mainCharacter->m_color);

        UpdateAgents();
        EndDrawing();
    }

    CloseWindow();
}

void Game::RegisterAgent(Agent* agent)
{
    m_agents.push_back(agent);
    std::cout << "Agent added to agents list. Agents amount: " << m_agents.size() << std::endl;
}

void Game::UnregisterAgent(Agent* agent)
{
    m_agentsToRemove.push_back(agent);
    cout << "Agent marked for removal" << endl;
}

void Game::UpdateAgents()
{
    for (auto const& i : m_agents) {
        if (i == NULL) {continue;}

        //Issue now is that I remove elements in the Update during the for loop
        i->Update();

        //Cast to projectile
        Projectile* projectile = dynamic_cast<Projectile*>(i);
        if (projectile != 0)
        {
            DrawCircle(i->m_posX, i->m_posY, projectile->m_radius, projectile->m_color);
        }
        else
        {
            //If the agent is not a projectile (you should differentiate them even more).
            //In fact, each agent could even implement it's own method Draw(),
            //Which would be even better.
            //This method would then only do i->Update(), and let agents draw themselves
            DrawRectangle(i->m_posX, i->m_posY, 5, 5, {255, 255, 0, 255});
        }
    }
    
    RemoveAgentsMarkedForRemoval();
}

//Complicated way of removing agents, only to be sure that we do it AFTER
    //updating every agent in a frame
void Game::RemoveAgentsMarkedForRemoval()
{
    for (int i = 0; i < m_agentsToRemove.size(); i++)
    {
        m_agents.remove(m_agentsToRemove[i]);
        delete(m_agentsToRemove[i]);
        std::cout << "Agent removed from agents list. Agents amount: " << m_agents.size() << std::endl;
    }
    m_agentsToRemove.clear();
    m_agentsToRemove.resize(0);
}