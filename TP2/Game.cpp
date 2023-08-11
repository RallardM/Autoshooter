#include <iostream>
#include <raylib.h>
#include "Game.h"

#include "GameObject.h"
#include "Projectile.h"
#include "MathUtils.h"



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
    Game* game = Game::GetInstance();
    game->StartGame();
    game->CleanUpGame(); // TODO verify if it is propelry cleaning
    delete game;
    return 0;
}

Game* Game::GetInstance()
{
    if (_Instance == nullptr || NULL)
    {
        _Instance = new Game();
    }
    return _Instance;
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
    for (int i = 0; i < enemyAmount; i++)
    {
        RegisterGameObject(new Enemy());
        //m_gameObjectsEnemies.emplace_back(new Enemy());
    }

    //for (Enemy* enemy : m_gameObjectsEnemies)
    //{
    //    enemy->OnStart();
    //}

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

GameObject* Game::GetClosestGameObject(Vector2 position, EGameObjectType type)
{
    GameObject* closest = nullptr;
	float closestDistance = 0.f;

    for (GameObject* agent : _Instance->m_gameObjects)
    {
        if (agent->GetGameObjectType() == type)
        {
			float distance = Vector2Distance(position, agent->GetPosition());
            if (closest == nullptr || distance < closestDistance)
            {
				closest = agent;
				closestDistance = distance;
			}
		}
	}

	return closest;
}

bool Game::AreEnemyProjectileColliding(Rectangle enemy)
{
    for (GameObject* gameObject : _Instance->m_gameObjects)
    {
        if (gameObject->GetGameObjectType() == EGameObjectType::PROJECTILE)
        {
            Projectile* projectile = dynamic_cast<Projectile*>(gameObject);
            Vector2 projectilePosition = projectile->GetPosition();
            float projectileRadius = projectile->GetRadius();

            bool IsEnemyHitByProjectile = CheckCollisionCircleRec(projectilePosition, projectileRadius, enemy);
            if (IsEnemyHitByProjectile)
            {
				return true;
			}
		}
	}
    return false;
}

bool Game::ArePlayerEnemyColliding(Rectangle player)
{
    for (GameObject* gameObject : _Instance->m_gameObjects)
    {
        if (gameObject->GetGameObjectType() == EGameObjectType::ENEMY)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(gameObject);
            Vector2 enemyPosition = enemy->GetPosition();
            Rectangle enemyRect = enemy->GetRect();

            bool IsEnemyHitByProjectile = CheckCollisionRecs(player, enemyRect);
            if (IsEnemyHitByProjectile)
            {
                return true;
            }
        }
    }
    return false;
}

void Game::CleanUpGame()
{
    CleanupGameObjects();
    // TODO : Clean up other resources
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
    
    RemoveGameObjectsMarkedForRemoval();
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
    //updating every gameObject in a frame
void Game::RemoveGameObjectsMarkedForRemoval()
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

void Game::CleanupGameObjects()
{
    // Delete and remove objects from m_gameObjects
    for (GameObject* obj : m_gameObjectsToRemove)
    {
        m_gameObjects.remove(obj);
        delete obj;
    }
    m_gameObjectsToRemove.clear();

    //// Delete and remove enemies from m_gameObjectsEnemies
    //for (Enemy* enemy : m_gameObjectsEnemies)
    //{
    //    m_gameObjects.remove(enemy); // Make sure you remove from this list as well
    //    delete enemy;
    //}
    //m_gameObjectsEnemies.clear();

    // Delete and remove projectiles from m_gameObjectsProjectiles
    //for (Projectile* enemy : m_gameObjectsProjectiles)
    //{
    //    m_gameObjects.remove(enemy); // Make sure you remove from this list as well
    //    delete enemy;
    //}
    //m_gameObjectsProjectiles.clear();

    for (GameObject* obj : m_gameObjects)
    {
		delete obj;
	}

    // TODO : verify and add any new list of objects to clean up here (Player, Weapons)
}
