#include <iostream>

#include "Game.h"
#include "Player.h"
#include "GameObject.h"
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

    m_player = new Player();
    m_player->OnStart();
    MainLoop();
}

void Game::MainLoop()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        RenderBackground();
        
        m_player->HandleInput();
        UpdateGameObjects();
        RenderGameObjects();
        EndDrawing();
    }

    CloseWindow();
}

void Game::RegisterAgent(GameObject* agent)
{
    m_agents.push_back(agent);
    std::cout << "Agent added to agents list. Agents amount: " << m_agents.size() << std::endl;
}

void Game::UnregisterAgent(GameObject* agent)
{
    m_agentsToRemove.push_back(agent);
    cout << "Agent marked for removal" << endl;
}

void Game::RenderBackground()
{
    ClearBackground(RAYWHITE);

    // Render grid
    // Source : Cours Algebre Vectoriel
    for (int i = 0; i < COLUMN_COUNT; ++i)
    {
        Vector2 start = { CELL_SIZE * i, 0.f };
        Vector2 end = { CELL_SIZE * i, SCREEN_HEIGHT };
        DrawLineV(start, end, DARKGRAY);
    }

    for (int i = 0; i < ROW_COUNT; ++i)
    {
        Vector2 start = { 0.f, CELL_SIZE * i };
        Vector2 end = { SCREEN_WIDTH, CELL_SIZE * i };
        DrawLineV(start, end, DARKGRAY);
    }
}

void Game::UpdateGameObjects()
{
    for (auto const& i : m_agents) {
        if (i == NULL) {continue;}

        //Issue now is that I remove elements in the Update during the for loop
        i->Update();

        ////Cast to projectile
        //Projectile* projectile = dynamic_cast<Projectile*>(i);
        //if (projectile != 0)
        //{
        //    DrawCircle((int)i->m_position.x, (int)i->m_position.y, projectile->m_radius, projectile->m_color);
        //}
        //else
        //{
        //    //If the agent is not a projectile (you should differentiate them even more).
        //    //In fact, each agent could even implement it's own method Draw(),
        //    //Which would be even better.
        //    //This method would then only do i->Update(), and let agents draw themselves
        //    DrawRectangle((int)i->m_position.x, (int)i->m_position.y, 5, 5, {255, 255, 0, 255});
        //}
    }
    
    RemoveAgentsMarkedForRemoval();
}

void Game::RenderGameObjects()
{
    for (auto const& i : m_agents) {
        if (i == NULL) { continue; }

        i->Render();

        //Cast to projectile
        Projectile* projectile = dynamic_cast<Projectile*>(i);
        if (projectile != 0)
        {
            DrawCircle((int)i->m_position.x, (int)i->m_position.y, projectile->m_radius, projectile->m_color);
        }
        else
        {
            //If the agent is not a projectile (you should differentiate them even more).
            //In fact, each agent could even implement it's own method Draw(),
            //Which would be even better.
            //This method would then only do i->Update(), and let agents draw themselves
            DrawRectangle((int)i->m_position.x, (int)i->m_position.y, 5, 5, {255, 255, 0, 255});
        }
    }
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