#include <iostream>

#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Projectile.h"

using namespace std;

Game* Game::_Instance = 0;
Camera2D* Game::s_camera = nullptr;
const float Game::S_MAP_WIDTH = 1601.0f;
const float Game::S_MAP_HEIGHT = 1601.0f;

int main(void)
{
    Game* game = new Game();
    game->StartGame();

    return 0;
}

void Game::StartGame()
{
    _Instance = this;
    InitWindow(S_CAMERA_WIDTH, S_CAMERA_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(60);

    m_player = new Player();
    m_player->OnStart();

    s_camera = new Camera2D();
    s_camera->offset = { (float)S_CAMERA_WIDTH / 2, (float)S_CAMERA_HEIGHT / 2 };
    s_camera->rotation = 0.0f;
    s_camera->zoom = 0.8f;

    MainLoop();
}

void Game::RegisterAgent(GameObject* agent)
{
    m_gameObjects.push_back(agent);
    std::cout << "Agent added to agents list. Agents amount: " << m_gameObjects.size() << std::endl;
}

void Game::UnregisterAgent(GameObject* agent)
{
    m_gameObjectsToRemove.push_back(agent);
    cout << "Agent marked for removal" << endl;
}

void Game::UpdateCameraPosition(Vector2 playerPosition)
{
    s_camera->target = { playerPosition.x, playerPosition.y };
}

void Game::MainLoop()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update Data
        m_player->HandleInput();
        UpdateGameObjects();

        // Render
        BeginDrawing();
        BeginMode2D(*s_camera);
        RenderBackground();
        RenderGameObjects();
        EndMode2D();
        EndDrawing();
    }

    CloseWindow();
}

void Game::RenderBackground()
{
    ClearBackground(DARKBLUE);
    Color gridColor = GOLD;

    // Render grid
    // Source : Cours Algebre Vectoriel
    for (int i = 0; i < COLUMN_COUNT; ++i)
    {
        // Alternate grid color on even columns
        if (i % 2 == 0)
        {
            gridColor = SKYBLUE;
        }
        else
        {
            gridColor = GOLD;
        }

        Vector2 start = { CELL_SIZE * i, 0.f };
        Vector2 end = { CELL_SIZE * i, S_MAP_HEIGHT };
        DrawLineV(start, end, gridColor);
    }

    for (int i = 0; i < ROW_COUNT; ++i)
    {
        // Alternate grid color on even rows
        if (i % 2 == 0)
        {
            gridColor = SKYBLUE;
        }
        else
        {
			gridColor = GOLD;
		}

        Vector2 start = { 0.f, CELL_SIZE * i };
        Vector2 end = { S_MAP_WIDTH, CELL_SIZE * i };
        DrawLineV(start, end, gridColor);
    }
}

void Game::UpdateGameObjects()
{
    for (auto const& i : m_gameObjects) 
    {
        if (i == NULL) {continue;}

        //Issue now is that I remove elements in the Update during the for loop
        i->Update();
    }
    
    RemoveAgentsMarkedForRemoval();
}

void Game::RenderGameObjects()
{
    for (auto const& i : m_gameObjects) 
    {
        if (i == NULL) { continue; }

        i->Render();
    }
}

//Complicated way of removing agents, only to be sure that we do it AFTER
    //updating every agent in a frame
void Game::RemoveAgentsMarkedForRemoval()
{
    for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
    {
        m_gameObjects.remove(m_gameObjectsToRemove[i]);
        delete(m_gameObjectsToRemove[i]);
        std::cout << "Agent removed from agents list. Agents amount: " << m_gameObjects.size() << std::endl;
    }
    m_gameObjectsToRemove.clear();
    m_gameObjectsToRemove.resize(0);
}