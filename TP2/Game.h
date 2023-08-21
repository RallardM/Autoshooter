#pragma once


#include "Player.h"
#include "MenuManager.h"
#include "CameraManager.h"

class GameObject;
class Player;

class Game
{
	friend class CameraManager;
	friend class CollisionManager;
	friend class ExperienceOrb;
	friend class Player;
	friend class Enemy;
	friend class UIElement;

public:
	static Game* GetInstance();

private:
	// Static GetMapWidth() and GetMapHeight() permits player to access map size without having a reference to Game
	const float S_MAP_WIDTH = 1601.0f;
	const float S_MAP_HEIGHT = 1601.0f;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;



	bool m_isPaused = false;

	// Keep dynamically changing sizes bellow
	static Game* _Instance;
	CameraManager* m_cameraManager = nullptr;
	MenuManager* m_menuManager = nullptr;
	Camera2D* m_camera = nullptr;
	Player* m_player = nullptr;

public:
	~Game();
	void StartGame();

private:
	Game(); // Private constructor for singleton pattern
	void MainLoop();
	void RenderBackground();
	void UpdateEnemySpawner();

	// Game getters and setters
	bool const IsPaused() const { return m_isPaused; }
	void PauseGame() { m_isPaused = !m_isPaused; }

	// Map getters
	const float GetMapWidth() { return S_MAP_WIDTH; }
	const float GetMapHeight() { return S_MAP_HEIGHT; }

	// Player getters // TODO Extract experience to its own class
	Player* GetPlayer() { return m_player; }
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() { return m_player->m_totalExperience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; m_player->m_totalExperience += experience; }

};