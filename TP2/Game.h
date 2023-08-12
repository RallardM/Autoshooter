#pragma once
#include <list>
#include <vector>


#include "Enemy.h"
#include "Player.h"

class GameObject;
class Player;

class Game
{
	

public:
	//Game(const Game& obj) = delete; // Constructor for singleton pattern
	static Game* GetInstance();


private:
	static Game* _Instance;
	const int CAMERA_WIDTH = 1200;
	const int CAMERA_HEIGHT = 800;

	// Static GetMapWidth() and GetMapHeight() permits player to access map size without having a reference to Game
	const float S_MAP_WIDTH = 1601.0f;
	const float S_MAP_HEIGHT = 1601.0f;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;

	// Enemies properties
	const int MIN_ENEMY_AMOUNT = 5;
	const int MAX_ENEMY_AMOUNT = 10;

	Player* m_player;
	//std::list<Enemy*> m_gameObjectsEnemies;
	//std::list<Projectile*> m_gameObjectsProjectiles;
	Camera2D* m_camera;

	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;


public:
	void StartGame();
	void RegisterGameObject(GameObject* agent);
	void UnregisterGameObject(GameObject* agent);
	void UpdateCameraPosition(Vector2 playerPosition);

	// Map getters
	const float GetMapWidth() { return S_MAP_WIDTH; }
	const float GetMapHeight() { return S_MAP_HEIGHT; }

	// Camera getters
	const float GetCameraLeftLimit() { return m_camera->target.x - (CAMERA_WIDTH / 2) / m_camera->zoom; }
	const float GetCameraRightLimit() { return m_camera->target.x + (CAMERA_WIDTH / 2) / m_camera->zoom; }
	const float GetCameraTopLimit() { return m_camera->target.y - (CAMERA_HEIGHT / 2) / m_camera->zoom; }
	const float GetCameraBottomLimit() { return m_camera->target.y + (CAMERA_HEIGHT / 2) / m_camera->zoom; }
	Vector2 GetCameraPosition() { return m_camera->target; }
	bool IsWithinCameraBounds(Vector2 position) { return position.x >= GetCameraLeftLimit() && position.x <= GetCameraRightLimit() && position.y >= GetCameraTopLimit() && position.y <= GetCameraBottomLimit(); }

	// Player getters
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; }

	// Game objects getter
	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }

	// Ennemies getters
	//std::list<Enemy*> GetEnemies() { return m_gameObjectsEnemies; }

	// Projectiles getters setters
	//void AddProjectileToList(Projectile* projectile) { m_gameObjectsProjectiles.emplace_back(projectile); };
	//std::list<Projectile*> GetProjectiles() { return m_gameObjectsProjectiles; }

	GameObject* GetClosestGameObject(Vector2 position, EGameObjectType type);
	bool AreEnemyProjectileColliding(Rectangle enemy);
	bool AreOrbPlayerColliding(Vector2 orbPosition, float orbradius);
	bool ArePlayerEnemyColliding(Rectangle player);

	void CleanUpGame();

private:
	Game() : m_camera(nullptr), m_player(nullptr) {} // Private constructor for singleton pattern
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects();
	unsigned short int GetObjectOfTypeCountFromList(EGameObjectType type);
	void RenderGameObjects();
	void RemoveGameObjectsMarkedForRemoval();
	void CleanupGameObjects();
};
