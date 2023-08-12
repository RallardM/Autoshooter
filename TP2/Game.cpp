#include <iostream>
#include <raylib.h>

#include "Game.h"
#include "GameObject.h"
#include "Projectile.h"
#include "MathUtils.h"

using namespace std;

Game* Game::_Instance = 0;

int main(void)
{
    Game* game = Game::GetInstance();
    game->StartGame();
    game->CleanUpGame(); // TODO verify if it is propelry cleaning
    delete game;
    return 0;
}

Game::~Game()
{
    delete m_player;
	delete m_camera;
    
 //   for (Enemy* enemy : m_enemyPool)
 //   {
	//	delete enemy;
	//}

 //   m_enemyPool.clear();

    for (GameObject* gameObject : m_gameObjects)
    {
		delete gameObject;
	}

	m_gameObjects.clear();

    for (GameObject* gameObject : m_gameObjectsToRemove)
    {
		delete gameObject;
	}

	m_gameObjectsToRemove.clear();
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

 //   // Initialize enemies pool
 //   for (int i = 0; i < MAX_ENEMY_AMOUNT; i++)
 //   {
 //       Enemy* enemy = new Enemy();
 //       m_enemyPool.push_back(enemy);
 //       RegisterGameObject(enemy);
	//}

    MainLoop();
}

void Game::RegisterGameObject(GameObject* gameObject)
{
    m_gameObjects.push_back(gameObject);
    //std::cout << "GameObject added to gameObjects list. GameObjects amount: " << m_gameObjects.size() << std::endl;
}

void Game::UnregisterGameObject(GameObject* gameObject)
{
    m_gameObjectsToRemove.push_back(gameObject);
    //cout << "GameObject marked for removal" << endl;
}

void Game::UpdateCameraPosition(Vector2 playerPosition)
{
    _Instance->m_camera->target = { playerPosition.x, playerPosition.y };
}

const unsigned short int Game::GetEntityHealth(GameObject* entity) const
{
    switch (entity->GetGameObjectType())
    {
        case EGameObjectType::PLAYER:
			return m_player->GetHealth();
			break;

        case EGameObjectType::ENEMY:
            return dynamic_cast<Enemy*>(entity)->GetHealth();
            break;

        case EGameObjectType::COUNT:
            default:
			std::cout << "Game::GetEntityHealth() : wrong entity type" << std::endl;
			return 0;
			break;
    }
}

//void Game::ReturnEnemyToPool(Enemy* enemy)
//{
//	m_enemyPool.push_back(enemy);
//}

GameObject* Game::GetClosestGameObject(Vector2 position, EGameObjectType type)
{
    GameObject* closest = nullptr;
	float closestDistance = 0.f;

    for (GameObject* gameObject : _Instance->m_gameObjects)
    {
        if (gameObject->GetGameObjectType() == type)
        {
			float distance = Vector2Distance(position, gameObject->GetPosition());
            if (closest == nullptr || distance < closestDistance)
            {
				closest = gameObject;
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

bool Game::AreOrbPlayerColliding(Vector2 orbPosition, float orbradius)
{
    bool IsEnemyHitByProjectile = CheckCollisionCircleRec(orbPosition, orbradius, _Instance->m_player->GetRect());
    if (IsEnemyHitByProjectile)
    {
		return true;
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
        UpdateGameObjects(GetFrameTime());

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
    Color gridColor = DARKGRAY;

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
            gridColor = DARKGRAY;
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
			gridColor = DARKGRAY;
		}

        Vector2 start = { 0.f, CELL_SIZE * i };
        Vector2 end = { S_MAP_WIDTH, CELL_SIZE * i };
        DrawLineV(start, end, gridColor);
    }
}

void Game::UpdateGameObjects(float deltatime)
{
    //unsigned short int enemiesCount = GetActiveObjectCountFromList(EGameObjectType::ENEMY);
    //
    //if (enemiesCount < MAX_ENEMY_AMOUNT)
    //{
    //    // Find an available enemy from the pool
    //    Enemy* enemy = nullptr;
    //    for (Enemy* poolEnemy : m_enemyPool)
    //    {
    //        if (!poolEnemy->IsActive())
    //        {
    //            enemy = poolEnemy;
    //            break;
    //        }
    //    }

    //    if (enemy)
    //    {
    //        RegisterGameObject(enemy);
    //        enemy->OnStart();
    //    }
    //}

    for (auto const& i : m_gameObjects) 
    {
        if (i == NULL) {continue;}

        if (i->IsActive() == false)
        {
            continue;
        }

        //Issue now is that I remove elements in the Update during the for loop
        i->Update(deltatime);
    }

    UpdateEnemySpawner();
    RemoveGameObjectsMarkedForRemoval();
}

unsigned short int Game::GetActiveObjectCountFromList(EGameObjectType type)
{
    unsigned short int count = 0;
    for (auto const& i : m_gameObjects)
    {
		if (i == NULL) { continue; }

        if (i->GetGameObjectType() == type && i->IsActive())
        {
			count++;
		}
	}

    return count;
}

void Game::RenderGameObjects()
{
    for (auto const& i : m_gameObjects) 
    {
        if (i == NULL) { continue; }

        if (i->IsActive() == false)
        {
            continue;
        }

        i->Render();
    }
}

void Game::UpdateEnemySpawner()
{
    unsigned short int enemiesCount = GetActiveObjectCountFromList(EGameObjectType::ENEMY);

    if (enemiesCount < MAX_ENEMY_AMOUNT)
    {
        Enemy* enemy = new Enemy();

        enemy->OnStart();
    }
}

//Complicated way of removing GameObjects, only to be sure that we do it AFTER
    //updating every gameObject in a frame
void Game::RemoveGameObjectsMarkedForRemoval()
{
    for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
    {
        EGameObjectType type = m_gameObjectsToRemove[i]->GetGameObjectType(); // TODO delete after debug
        bool isActive = m_gameObjectsToRemove[i]->IsActive(); // TODO delete after debug
        if (type == EGameObjectType::ENEMY)
        {
            std::cout << "GameObject is an enemy" << std::endl;
        }

        m_gameObjects.remove(m_gameObjectsToRemove[i]);
        delete(m_gameObjectsToRemove[i]);
       // std::cout << "GameObject removed from gameObjects list. GameObjects amount: " << m_gameObjects.size() << std::endl;
    

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


    for (GameObject* obj : m_gameObjects)
    {
		delete obj;
	}

    // TODO : verify and add any new list of objects to clean up here (Player, Weapons)
}

