#pragma once
#include <list>
#include <vector>

#include "Player.h"
#include "MenuManager.h"
#include "CameraManager.h"

class GameObject;
class Player;

class Game
{
public:
	static Game* GetInstance();

private:
	// Static GetMapWidth() and GetMapHeight() permits player to access map size without having a reference to Game
	const float S_MAP_WIDTH = 1601.0f;
	const float S_MAP_HEIGHT = 1601.0f;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;

	// Enemies properties
	const int MAX_ENEMY_AMOUNT = 10;

	bool m_isPaused = false;

	// Keep dynamically changing sizes bellow
	static Game* _Instance;
	CameraManager* m_cameraManager = nullptr;
	MenuManager* m_menuManager = nullptr;
	Camera2D* m_camera = nullptr;
	Player* m_player = nullptr;

	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;

public:
	~Game();
	void StartGame();

	// Game getters and setters
	bool const IsPaused() const { return m_isPaused; }
	void PauseGame() { m_isPaused = !m_isPaused; }


	// GameObjects Methods
	void RegisterGameObject(GameObject* agent);
	void UnregisterGameObject(GameObject* agent);

	// Map getters
	const float GetMapWidth() { return S_MAP_WIDTH; }
	const float GetMapHeight() { return S_MAP_HEIGHT; }

	// Player getters // TODO Extract experience to its own class
	Player* GetPlayer() { return m_player; }
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() { return m_player->m_totalExperience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; m_player->m_totalExperience += experience; }

	// Game objects getter
	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }
	EGameObjectType GetGameObjectType(GameObject* gameObject);
	GameObject* GetClosestGameObject(Vector2 position, EGameObjectType type);

private:
	Game(); // Private constructor for singleton pattern
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects(float deltatime);
	unsigned short int GetActiveObjectCountFromList(EGameObjectType type);
	void RenderGameObjects();
	void UpdateEnemySpawner();
	void RemoveGameObjectsMarkedForRemoval();

	void ResetAllObjects();
	void UnegisterAllObjects();
	void RemoveAllGameObjects();
	void CleanUpGame();
	
};