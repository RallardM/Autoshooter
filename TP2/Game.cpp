#include <iostream>
#include <raylib.h>

#include "Game.h"
#include "GameObject.h"
#include "Projectile.h"

#include "CollisionManager.h"
#include "GameObjectPool.h"

using namespace std;

Game* Game::_Instance = nullptr;

Game::Game()
{
	std::cout << "Game constructor called" << std::endl;
}

Game::~Game()
{
	std::cout << "Game destructor called" << std::endl;
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
	SetTargetFPS(TARGET_FPS);

	// Initialize player
	m_player = new Player();
	m_player->OnStart();

	MainLoop();
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
		GameObjectPool::GetInstance()->RenderGameObjects();

		if (m_isPaused)
		{
			MenuManager::GetInstance()->RenderPause();
		}
		else
		{
			float deltaTime = GetFrameTime();
			UpdateEnemySpawner();
			GameObjectPool::GetInstance()->RemoveGameObjectsMarkedForRemoval();
			GameObjectPool::GetInstance()->UpdateGameObjects(deltaTime);
		}

		EndMode2D();
		EndDrawing();
	}

	GameObjectPool::GetInstance()->CleanUpGame();
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
		// Alternate grid color on even (%2) columns
		if (i % EVEN == 0)
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
		// Alternate grid color on even (%2) rows
		if (i % EVEN == 0)
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

void Game::UpdateEnemySpawner()
{
	EGameObjectType enemyType = EGameObjectType::ENEMY;
	unsigned short int enemiesCount = GameObjectPool::GetInstance()->GetActiveObjectCountFromList(enemyType);

	if (enemiesCount < MAX_ENEMY_AMOUNT_PER_LEVELS * m_player->GetLevel())
	{
		Enemy* enemy = new Enemy();

		enemy->OnStart();
	}
}
