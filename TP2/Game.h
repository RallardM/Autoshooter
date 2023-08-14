#pragma once
#include <list>
#include <vector>

#include "Enumerations.h"
#include "Enemy.h"
#include "Player.h"
#include "MenuManager.h"
#include "CameraManager.h"

class GameObject;
class Player;

class Game
{
public:
	~Game();
	static Game* GetInstance();

private:
	// Static GetMapWidth() and GetMapHeight() permits player to access map size without having a reference to Game
	const float S_MAP_WIDTH = 1601.0f;
	const float S_MAP_HEIGHT = 1601.0f;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;

	// Enemies properties
	const int MIN_ENEMY_AMOUNT = 5;
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
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() { return m_player->m_totalExperience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; m_player->m_totalExperience += experience; }

	// Game objects getter
	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }
	GameObject* GetClosestGameObject(Vector2 position, EGameObjectType type);
	GameObject* GetObjectFromId(unsigned short int gameObjectId);

	// Collision detection // TODO Extract collision detection to its own class
	bool AreEnemyProjectileColliding(Rectangle enemy);
	Projectile* GetCollidingProjectile(Rectangle enemy);
	bool AreOrbPlayerColliding(Vector2 orbPosition, float orbradius);
	bool ArePlayerEnemyColliding(Rectangle player);
	Enemy* GetCollidingEnemy(Rectangle player);

private:
	Game() {} // Private constructor for singleton pattern
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects(float deltatime);
	unsigned short int GetActiveObjectCountFromList(EGameObjectType type);
	void RenderGameObjects();
	void UpdateEnemySpawner();
	void RemoveGameObjectsMarkedForRemoval();
	void CleanupGameObjects();

public:
	void CleanUpGame();
	
};