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
    m_camera->offset = { (float)CAMERA_WIDTH * HALF, (float)CAMERA_HEIGHT * HALF };
    m_camera->rotation = 0.0f;
    m_camera->zoom = 0.8f;

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
        if (gameObject == nullptr) { continue;}

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

Projectile* Game::GetCollidingProjectile(Rectangle enemy)
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
                return projectile;
            }
        }
    }
    return nullptr;
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
        if (gameObject == nullptr) { continue; }

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

Enemy* Game::GetCollidingEnemy(Rectangle player)
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
				return enemy;
			}
		}
	}
	return nullptr;
}

void Game::MainLoop()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update Data
        m_player->HandleInput();

        // Render
        BeginDrawing();
        BeginMode2D(*m_camera);

        RenderBackground();
        RenderGameObjects();

        if (m_isPaused) 
        { 
            RenderPause(); 
        }
        else 
        { 
            UpdateGameObjects(GetFrameTime());
        }

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

void Game::RenderPause()
{
    if (m_isPlayerDeadMenuOn)
    {
		RenderGameOver();
        return;
	}

    if (m_isLevelUpMenuOn)
    {
        RenderLevelUp();
    }
}

void Game::RenderLevelUp()
{
    float zoom = m_camera->zoom;

    // Get the top-left corner, width, and height of the camera
    Vector2 topLeftCorner = GetCameraTopLeftCorner();
    float cameraWidth = GetCameraWidth();
    float cameraHeight = GetCameraHeight();

    // Adjust the width and height of the rectangle based on the zoom value
    float adjustedWidth = cameraWidth / zoom;
    float adjustedHeight = cameraHeight / zoom;

    float halfWidth = adjustedWidth * HALF;
    float halfHeight = adjustedHeight * HALF;

    // Draw background
    DrawRectangle((int)topLeftCorner.x, (int)topLeftCorner.y, (int)adjustedWidth, (int)adjustedHeight, Fade(BLACK, 0.5f));

    // Draw Menu Box
    float menuBoxWidth = 400;
    float menuBoxHeight = 700;
    float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
    float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
    Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
    DrawRectangleRounded(menuBox, 0.1f, 12, LIGHTGRAY);

    // Draw text

    // Level Up
    string levelUpText = "Level Up!";
    int menuFontSize = 40;
    float textHeight = menuFontSize * HALF;
    int textWidth = MeasureText(levelUpText.c_str(), menuFontSize);
    float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    float uiPositionY = menuBox.y + textHeight;
    DrawText(levelUpText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);

    // Upgrades

    // Shooting rate
    string shootingRateText = "1 Shooting Rate x 2";
    int choicesFontSize = 30;
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(shootingRateText.c_str(), choicesFontSize);
    float offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(shootingRateText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // Shooting Damage
    string shootingDamageText = "2 Shooting Damage x 2";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(shootingDamageText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(shootingDamageText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // Projectile Size
    string bulletSizeText = "3 Projectile Size x 2";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(bulletSizeText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(bulletSizeText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // Health Capacity
    string healthCapText = "4 Health Bonus + 10";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(healthCapText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH ;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(healthCapText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // New HandGun
    string newHandGunText = "5 New HandGun";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(newHandGunText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(newHandGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // New Eplosive Gun
    string newExplosiveGunText = "6 New Explosive Gun";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(newExplosiveGunText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(newExplosiveGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

    // New Laser Gun
    string newLaserGunText = "7 New Laser Gun";
    textHeight = choicesFontSize * HALF;
    textWidth = MeasureText(newLaserGunText.c_str(), choicesFontSize);
    offsetDown = menuBoxHeight * EIGHTH;
    uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    uiPositionY += offsetDown;
    DrawText(newLaserGunText.c_str(), (int)uiPositionX, (int)uiPositionY, choicesFontSize, DARKBLUE);

}

void Game::RenderGameOver()
{
    float zoom = m_camera->zoom;

    // Get the top-left corner, width, and height of the camera
    Vector2 topLeftCorner = GetCameraTopLeftCorner();
    float cameraWidth = GetCameraWidth();
    float cameraHeight = GetCameraHeight();

    // Adjust the width and height of the rectangle based on the zoom value
    float adjustedWidth = cameraWidth / zoom;
    float adjustedHeight = cameraHeight / zoom;

    float halfWidth = adjustedWidth * HALF;
    float halfHeight = adjustedHeight * HALF;

    // Draw background
    DrawRectangle((int)topLeftCorner.x, (int)topLeftCorner.y, (int)adjustedWidth, (int)adjustedHeight, Fade(BLACK, 0.5f));

    // Draw Menu Box
    float menuBoxWidth = 400;
    float menuBoxHeight = 100;
    float menuBoxXPosition = topLeftCorner.x + halfWidth - menuBoxWidth * HALF;
    float menuBoxYPosition = topLeftCorner.y + halfHeight - menuBoxHeight * HALF;
    Rectangle menuBox = { menuBoxXPosition, menuBoxYPosition, menuBoxWidth, menuBoxHeight };
    DrawRectangleRounded(menuBox, 0.1f, 12, LIGHTGRAY);

    // Draw text

    // Level Up
    string levelUpText = "Game Over!";
    int menuFontSize = 40;
    float textHeight = menuFontSize * HALF;
    int textWidth = MeasureText(levelUpText.c_str(), menuFontSize);
    float uiPositionX = menuBox.x + menuBox.width * HALF - textWidth * HALF;
    float uiPositionY = menuBox.y + textHeight;
    DrawText(levelUpText.c_str(), (int)uiPositionX, (int)uiPositionY, menuFontSize, DARKBLUE);
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
        // TODO delete after debug end of production
        //EGameObjectType type = m_gameObjectsToRemove[i]->GetGameObjectType(); 
        //bool isActive = m_gameObjectsToRemove[i]->IsActive();
        //if (type == EGameObjectType::ENEMY)
        //{
        //    std::cout << "GameObject is an enemy" << std::endl;
        //}

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

void Game::CleanUpGame()
{
    CleanupGameObjects();
    // TODO : Clean up other resources
}