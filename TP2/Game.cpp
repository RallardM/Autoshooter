#include <iostream>
#include <raylib.h>

#include "Game.h"
#include "GameObject.h"
#include "Projectile.h"

#include "CollisionManager.h"
#include "GameObjectPool.h"
#include "MenuManager.h"

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

void Game::MainLoop()
{
	// Update the GameObjects at least once so it gives a better camera angle on the Main menu
	float deltaTime = GetFrameTime();
	GameObjectPool::GetInstance()->UpdateGameObjects(deltaTime);

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update Data
		GameObjectPool::GetInstance()->m_player->HandleInput();

		// Render
		BeginDrawing();
		BeginMode2D(*GameObjectPool::GetInstance()->m_camera);

		RenderBackground();
		GameObjectPool::GetInstance()->RenderGameObjects();

		if (m_isPaused)
		{

			MenuManager::GetInstance()->RenderPause();
		}
		else
		{
			float deltaTime = GetFrameTime();
			GameObjectPool::GetInstance()->UpdateGameObjects(deltaTime);
			GameObjectPool::GetInstance()->UpdateEnemySpawner();
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
		Vector2 end = { CELL_SIZE * i, MAP_HEIGHT };
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
		Vector2 end = { MAP_WIDTH, CELL_SIZE * i };
		DrawLineV(start, end, gridColor);
	}
}