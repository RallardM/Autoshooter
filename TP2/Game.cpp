#include <iostream>
#include <raylib.h>

#include "Game.h"
#include "GameObject.h"
#include "Projectile.h"
#include "MathUtils.h"
#include "CollisionManager.h"

using namespace std;

Game* Game::_Instance = nullptr;

Game::Game()
{
	std::cout << "Game constructor called" << std::endl;
}

Game::~Game()
{
	std::cout << "Game destructor called" << std::endl;

	// Delete Experience Orbs
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		if (gameObject->GetGameObjectType() != EGameObjectType::ORB) { continue; }
		delete gameObject;
		gameObject = nullptr;
	}

	// Delete Projectiles
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		if (gameObject->GetGameObjectType() != EGameObjectType::PROJECTILE) { continue; }
		delete gameObject;
		gameObject = nullptr;
	}

	// Delete UI Elements
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		if (gameObject->GetGameObjectType() != EGameObjectType::UI) { continue; }
		delete gameObject;
		gameObject = nullptr;
	}

	// Delete Enemies
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		if (gameObject->GetGameObjectType() != EGameObjectType::ENEMY) { continue; }

		delete gameObject;
		gameObject = nullptr;
	}

	// Delete Player's weapon
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		if (gameObject->GetGameObjectType() != EGameObjectType::WEAPON) { continue; }

		delete gameObject;
		gameObject = nullptr;
	}

	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		delete gameObject;
		gameObject = nullptr;
	}
	m_gameObjects.clear();

	if (m_menuManager != nullptr)
	{
		delete m_menuManager;
		m_menuManager = nullptr;
	}

	if (m_cameraManager != nullptr)
	{
		delete m_cameraManager;
		m_cameraManager = nullptr;
	}

	// Delete the camera 
	delete CameraManager::GetInstance();

	// Delete the menu manager
	delete MenuManager::GetInstance();

	// Delete the collision manager
	delete CollisionManager::GetInstance();
}

Game* Game::GetInstance()
{
	if (_Instance == nullptr)
	{
		_Instance = new Game();
	}
	return _Instance;
}

void Game::StartGame()
{
	// Initialize random seed
	srand(static_cast<unsigned int>(time(NULL))); // cast for the warning :  C4244: 'argument': conversion from 'time_t' to 'unsigned int', possible loss of data

	// Initialize camera manager
	CameraManager* m_cameraManager = CameraManager::GetInstance();
	m_cameraManager->InitializeCamera();
	m_camera = m_cameraManager->GetCamera();

	_Instance = this;
	InitWindow((int)m_cameraManager->GetCameraWidth(), (int)m_cameraManager->GetCameraHeight(), "raylib [core] example - basic window");
	SetTargetFPS(60);

	// Initialize player
	m_player = new Player();
	m_player->OnStart();

	MainLoop();
}

void Game::RegisterGameObject(GameObject* gameObject)
{
	m_gameObjects.push_back(gameObject);
	//std::cout << "GameObject added to gameObjects list. GameObjects amount: " << m_gameObjects.size() << std::endl;
}

EGameObjectType Game::GetGameObjectType(GameObject* gameObject)
{
	return gameObject->GetGameObjectType();
}

GameObject* Game::GetClosestGameObject(const Vector2& position, const EGameObjectType& type)
{
	GameObject* closest = nullptr;
	float closestDistance = 0.f;

	for (GameObject* gameObject : _Instance->m_gameObjects)
	{
		if (gameObject->GetGameObjectType() == type)
		{
			float distance = GetFloatDistanceBetweenTwoVects(position, gameObject->GetPosition());
			if (closest == nullptr || distance < closestDistance)
			{
				closest = gameObject;
				closestDistance = distance;
			}
		}
	}

	return closest;
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
			MenuManager::GetInstance()->RenderPause();
		}
		else
		{
			float deltaTime = GetFrameTime();
			UpdateGameObjects(deltaTime);
		}

		EndMode2D();
		EndDrawing();
	}

	CleanUpGame();
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

void Game::UpdateGameObjects(const float& deltatime)
{
	UpdateEnemySpawner();
	UpdateEnemies(deltatime); // Clears UI healthbars on Enemy first to avoid deleting an entity that contains a UI element pointer

	auto it = m_gameObjects.begin();
	while (it != m_gameObjects.end()) 
	{
		GameObject* gameObject = *it;
		if (gameObject == NULL) 
		{
			++it;
			continue;
		}

		if (gameObject->GetGameObjectType() == EGameObjectType::UI)
		{
			++it;
			continue;
		}

		// Update the game object
		gameObject->Update(deltatime);

		if (gameObject->IsActive() == false && gameObject->GetIsSetToDestroy() == true) 
		{
			it = m_gameObjects.erase(it);
			delete gameObject;
			gameObject = nullptr;
		}
		else 
		{
			++it;
		}
	}

	//for (GameObject* gameObject : m_gameObjects)
	//{
	//	if (gameObject == NULL) { continue; }
	//	if (gameObject->GetGameObjectType() == EGameObjectType::UI) { continue; }

	//	if (gameObject->IsActive() == false && gameObject->GetIsSetToDestroy() == true)
	//	{
	//		m_gameObjects.remove(gameObject);
	//		delete gameObject;
	//		gameObject = nullptr;
	//		continue;
	//	}

	//	gameObject->Update(deltatime);
	//}
}

unsigned short int Game::GetActiveObjectCountFromList(const EGameObjectType& type)
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
	EGameObjectType enemyType = EGameObjectType::ENEMY;
	unsigned short int enemiesCount = GetActiveObjectCountFromList(enemyType);

	if (enemiesCount < MAX_ENEMY_AMOUNT * m_player->GetLevel())
	{
		Enemy* enemy = new Enemy();

		enemy->OnStart();
	}
}

void Game::UpdateEnemies(const float& deltatime)
{
	auto it = m_gameObjects.begin();
	while (it != m_gameObjects.end())
	{
		GameObject* gameObject = *it;
		if (gameObject == NULL)
		{
			++it;
			continue;
		}

		if (gameObject->GetGameObjectType() != EGameObjectType::ENEMY)
		{
			++it;
			continue;
		}

		// Dynamic cast to Enemy
		Enemy* enemy = dynamic_cast<Enemy*>(gameObject);

		// Update the game object
		enemy->Update(deltatime);

		if (enemy->IsActive() == false && enemy->GetIsSetToDestroy() == true)
		{
			enemy->DestroyUIElements();
			it = m_gameObjects.erase(it);
			delete enemy;
			enemy = nullptr;
		}
		else
		{
			++it;
		}
	}


	//for (GameObject* gameObject : m_gameObjects)
	//{
	//	if (gameObject == NULL) { continue; }
	//	if (gameObject->GetGameObjectType() != EGameObjectType::UI) { continue; }

	//	if (gameObject->IsActive() == false && gameObject->GetIsSetToDestroy() == true)
	//	{
	//		std::cout << "Removing UI element ID : " << gameObject->m_gameObjectId << std::endl;
	//		m_gameObjects.remove(gameObject);
	//		delete gameObject;
	//		gameObject = nullptr;
	//		continue;
	//	}

	//	gameObject->Update(deltatime);
	//}
}

////Complicated way of removing GameObjects, only to be sure that we do it AFTER
//	//updating every gameObject in a frame
//void Game::RemoveGameObjectsMarkedForRemoval()
//{
//	for (GameObject* gameObject : m_gameObjects)
//	{
//		if (gameObject == nullptr) { continue; }
//		if (gameObject->IsActive() == true) { continue; }
//		if (gameObject->GetIsSetToDestroy() == false) { continue; }
//		
//		delete gameObject;
//		gameObject = nullptr;
//	}
//}

void Game::RemoveAllGameObjects()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		delete gameObject;
		gameObject = nullptr;
	}

	m_gameObjects.clear();
	m_gameObjects.resize(0);
}

void Game::CleanUpGame()
{
	RemoveAllGameObjects();
}