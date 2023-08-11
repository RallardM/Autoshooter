#pragma once
#include <list>
#include <vector>


#include "Enemy.h"
#include "Player.h"

class GameObject;
class Player;

class Game
{
	static Game* _Instance;

public:
	//Game(const Game& obj) = delete; // Constructor for singleton pattern
	static Game* GetInstance();


private:
	const int CAMERA_WIDTH = 1200;
	const int CAMERA_HEIGHT = 800;

	// Static GetMapWidth() and GetMapHeight() permits player to access map size without having a reference to Game
	const float S_MAP_WIDTH = 1601.0f;
	const float S_MAP_HEIGHT = 1601.0f;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;

	// Enemies properties
	const int MIN_ENEMY_AMOUNT = 8;
	const int MAX_ENEMY_AMOUNT = 10;

	Player* m_player;
	std::list<Enemy*> m_gameObjectsEnemies;
	std::list<Projectile*> m_gameObjectsProjectiles;
	Camera2D* m_camera;

	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;


public:
	void StartGame();
	void RegisterGameObject(GameObject* agent);
	void UnregisterGameObject(GameObject* agent);
	static void UpdateCameraPosition(Vector2 playerPosition);

	// Map getters
	static const float GetMapWidth() { return _Instance->S_MAP_WIDTH; }
	static const float GetMapHeight() { return _Instance->S_MAP_HEIGHT; }

	// Camera getters
	static float GetCameraLeftLimit() { return _Instance->m_camera->target.x - (_Instance->CAMERA_WIDTH / 2) / _Instance->m_camera->zoom; }
	static float GetCameraRightLimit() { return _Instance->m_camera->target.x + (_Instance->CAMERA_WIDTH / 2) / _Instance->m_camera->zoom; }
	static float GetCameraTopLimit() { return _Instance->m_camera->target.y - (_Instance->CAMERA_HEIGHT / 2) / _Instance->m_camera->zoom; }
	static float GetCameraBottomLimit() { return _Instance->m_camera->target.y + (_Instance->CAMERA_HEIGHT / 2) / _Instance->m_camera->zoom; }
	static Vector2 GetCameraPosition() { return _Instance->m_camera->target; }
	static bool IsWithinCameraBounds(Vector2 position) { return position.x >= GetCameraLeftLimit() && position.x <= GetCameraRightLimit() && position.y >= GetCameraTopLimit() && position.y <= GetCameraBottomLimit(); }

	// Player getters
	static Vector2 GetPlayerPosition() { return { _Instance->m_player->m_position.x, _Instance->m_player->m_position.y }; }

	// Ennemies getters
	static std::list<Enemy*> GetEnemies() { return _Instance->m_gameObjectsEnemies; }

	static void AddProjectileToList(Projectile* projectile) { _Instance->m_gameObjectsProjectiles.emplace_back(projectile); };

	void CleanUpGame();

private:
	Game() {} // Private constructor for singleton pattern
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects();
	void RenderGameObjects();
	void RemoveAgentsMarkedForRemoval();
	void CleanupGameObjects();
};
