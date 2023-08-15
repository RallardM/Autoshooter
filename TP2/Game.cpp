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

	// Delete the player
	//if (m_player != nullptr)
	//{
	//	delete m_player;
	//	m_player = nullptr;
	//}

	// Delete Player's weapon
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }
		if (gameObject->GetGameObjectType() != EGameObjectType::WEAPON) { continue; }

		delete gameObject;
		gameObject = nullptr;
	}

	for (GameObject* gameObject : m_gameObjectsToRemove)
	{
		if (gameObject == nullptr) { continue; }
		delete gameObject;
		gameObject = nullptr;
	}
	m_gameObjectsToRemove.clear();

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

void Game::UnregisterGameObject(GameObject* gameObject)
{
	m_gameObjectsToRemove.push_back(gameObject);
	//cout << "GameObject marked for removal" << endl;
}


EGameObjectType Game::GetGameObjectType(GameObject* gameObject)
{
	return gameObject->GetGameObjectType();
}

GameObject* Game::GetClosestGameObject(Vector2 position, EGameObjectType type)
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
			UpdateGameObjects(GetFrameTime());
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

void Game::UpdateGameObjects(float deltatime)
{
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

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

	if (enemiesCount < MAX_ENEMY_AMOUNT * m_player->GetLevel())
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
		if (m_gameObjectsToRemove[i] == nullptr) { continue; }
		if (m_gameObjectsToRemove[i]->IsActive() == true) { continue; }

		auto iter = std::remove(m_gameObjects.begin(), m_gameObjects.end(), m_gameObjectsToRemove[i]);
		m_gameObjects.erase(iter);

		delete m_gameObjectsToRemove[i];
		m_gameObjectsToRemove[i] = nullptr;
	}

	m_gameObjectsToRemove.clear();
	m_gameObjectsToRemove.resize(0);

	for (GameObject* obj : m_gameObjects)
	{
		if (obj == nullptr) { continue; }
		if (obj->IsActive() == true) { continue; }

		m_gameObjectsToRemove.push_back(obj);
	}
}


void Game::ResetAllObjects()
{
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		i->Reset();
	}

	//m_gameObjects.clear();
	//m_gameObjects.resize(0);
}

void Game::UnegisterAllObjects()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		// if not in m_gameObjectsToRemove push_back to m_gameObjectsToRemove
		if (std::find(m_gameObjectsToRemove.begin(), m_gameObjectsToRemove.end(), gameObject) == m_gameObjectsToRemove.end())
		{
			m_gameObjectsToRemove.push_back(gameObject);
		}

	}
	//m_gameObjects.clear();
}


void Game::RemoveAllGameObjects()
{
	for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
	{
		if (m_gameObjectsToRemove[i] == nullptr) { continue; }

		auto iter = std::remove(m_gameObjects.begin(), m_gameObjects.end(), m_gameObjectsToRemove[i]);
		m_gameObjects.erase(iter);

		delete m_gameObjectsToRemove[i];
		m_gameObjectsToRemove[i] = nullptr;
	}

	m_gameObjectsToRemove.clear();
	m_gameObjectsToRemove.resize(0);

	for (GameObject* obj : m_gameObjects)
	{
		if (obj == nullptr) { continue; }

		delete obj;
		obj = nullptr;
	}

	m_gameObjects.clear();
	m_gameObjects.resize(0);
}

void Game::CleanUpGame()
{
	ResetAllObjects();
	UnegisterAllObjects();
	RemoveAllGameObjects();
}