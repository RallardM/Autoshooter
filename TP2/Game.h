#pragma once
#include <list>
#include <vector>

#include "Enumerations.h"
#include "Enemy.h"
#include "Player.h"
#include "MathUtils.h"

class GameObject;
class Player;

class Game
{
public:
	~Game();
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

	Player* m_player = nullptr;
	Camera2D* m_camera = nullptr;

	//std::list <Enemy*> m_enemyPool;
	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;

	bool m_isPaused = false;

public:
	void StartGame();
	void PauseGame();
	bool const IsPaused() const { return m_isPaused; }
	void RegisterGameObject(GameObject* agent);
	void UnregisterGameObject(GameObject* agent);
	void UpdateCameraPosition(Vector2 playerPosition);

	// Map getters
	const float GetMapWidth() { return S_MAP_WIDTH; }
	const float GetMapHeight() { return S_MAP_HEIGHT; }

	// Camera getters // TODO Extract camera to its own class
	const float GetCameraWidth() { return (float)CAMERA_WIDTH; }
	const float GetCameraHeight() { return (float)CAMERA_HEIGHT; }
	const float GetTransformedCameraWidth() { return (float)CAMERA_WIDTH / m_camera->zoom; }
	const float GetTransformedCameraHeight() { return (float)CAMERA_HEIGHT / m_camera->zoom; }
	// Camera limits
	//const float GetCameraLeftLimit() { return m_camera->target.x - (CAMERA_WIDTH * HALF) / m_camera->zoom; }
	//const float GetCameraRightLimit() { return m_camera->target.x + (CAMERA_WIDTH * HALF) / m_camera->zoom; }
	//const float GetCameraTopLimit() { return m_camera->target.y - (CAMERA_HEIGHT * HALF) / m_camera->zoom; }
	//const float GetCameraBottomLimit() { return m_camera->target.y + (CAMERA_HEIGHT * HALF) / m_camera->zoom; }
	const float GetCameraLeftLimit() { return (m_camera->target.x - m_camera->offset.x) / m_camera->zoom; }
	const float GetCameraRightLimit() { return (m_camera->target.x + m_camera->offset.x) / m_camera->zoom; }
	const float GetCameraTopLimit() { return (m_camera->target.y - m_camera->offset.y) / m_camera->zoom; }
	const float GetCameraBottomLimit() { return (m_camera->target.y + m_camera->offset.y) / m_camera->zoom; }

	const Vector2 GetCameraPosition() { return m_camera->target; }
	const Vector2 GetCameraOffset() { return m_camera->offset; }
	const float GetCameraZoom() { return m_camera->zoom; }
	const Vector2 GetCameraTopLeftCorner() { return { GetCameraLeftLimit(), GetCameraTopLimit() }; }
	const bool IsWithinCameraBounds(Vector2 position) { return position.x >= GetCameraLeftLimit() && position.x <= GetCameraRightLimit() && position.y >= GetCameraTopLimit() && position.y <= GetCameraBottomLimit(); }

	// Player getters // TODO Extract experience to its own class
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() { return m_player->m_totalExperience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; m_player->m_totalExperience += experience; }

	// Game objects getter
	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }
	GameObject* GetClosestGameObject(Vector2 position, EGameObjectType type);

	// Collision detection // TODO Extract collision detection to its own class
	bool AreEnemyProjectileColliding(Rectangle enemy);
	Projectile* GetCollidingProjectile(Rectangle enemy);
	bool AreOrbPlayerColliding(Vector2 orbPosition, float orbradius);
	bool ArePlayerEnemyColliding(Rectangle player);

	// Entities getters
	const unsigned short int GetEntityHealth(GameObject* entity) const;

private:
	Game() {} // Private constructor for singleton pattern
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects(float deltatime);
	void RenderPause();
	unsigned short int GetActiveObjectCountFromList(EGameObjectType type);
	void RenderGameObjects();
	void UpdateEnemySpawner();
	void RemoveGameObjectsMarkedForRemoval();
	void CleanupGameObjects();

public:
	void CleanUpGame();
	
};
