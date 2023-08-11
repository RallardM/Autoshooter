#include <iostream>

#include "Game.h"

#include "GameObject.h"
#include "Projectile.h"

using namespace std;

Game* Game::_Instance = 0;

//Game::~Game()
//{
//
//
//    //TODO: delete other pointer ojbects
//}

int main(void)
{
    Game* game = new Game();
    game->StartGame();

    return 0;
}

void Game::StartGame()
{
    _Instance = this;
    InitWindow(CAMERA_WIDTH, CAMERA_HEIGHT, "raylib [core] example - basic window");
    SetTargetFPS(60);

    // Initialize player
    m_player = new Player();
    m_player->OnStart();

    // Initialize camera
    m_camera = new Camera2D();
    m_camera->offset = { (float)CAMERA_WIDTH / 2, (float)CAMERA_HEIGHT / 2 };
    m_camera->rotation = 0.0f;
    m_camera->zoom = 0.8f;

    // Initialize enemies
    int enemyAmount = std::rand() % (MAX_ENEMY_AMOUNT - MIN_ENEMY_AMOUNT) + MIN_ENEMY_AMOUNT;
    for (int i = 0; i < enemyAmount; i++)// just for test 
    {
        m_gameObjectsEnemies.emplace_back(new Enemy());
    }

    if (!m_gameObjectsEnemies.empty())
    {
        for (int i = 0; i != m_gameObjectsEnemies.size(); ++i)
        {
            m_gameObjectsEnemies[i]->OnStart();
        }
    }

    MainLoop();
}

void Game::RegisterGameObject(GameObject* agent)
{
    m_gameObjects.push_back(agent);
    std::cout << "Agent added to agents list. Agents amount: " << m_gameObjects.size() << std::endl;
}

void Game::UnregisterGameObject(GameObject* agent)
{
    m_gameObjectsToRemove.push_back(agent);
    cout << "Agent marked for removal" << endl;
}

void Game::UpdateCameraPosition(Vector2 playerPosition)
{
    _Instance->m_camera->target = { playerPosition.x, playerPosition.y };
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
        BeginMode2D(*m_camera);
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