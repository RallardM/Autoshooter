#pragma once
#include <list>
#include <vector>

#include "raylib.h"
#include "Enemy.h"

class GameObject;
class Player;

class Game
{
	static Game* _Instance;

public:
	static Game* GetInstance() { return _Instance; } //Not a real singleton written like this
	//This should be adressed

public:


private:
	static const int S_CAMERA_WIDTH = 1200;
	static const int S_CAMERA_HEIGHT = 800;

	// Static GetMapWidth() and GetMapHeight() permits player to access map size without having a reference to Game
	static const float S_MAP_WIDTH;
	static const float S_MAP_HEIGHT;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;

	// Enemies properties
	const int MIN_ENEMY_AMOUNT = 8;
	const int MAX_ENEMY_AMOUNT = 10;

	Player* m_player;
	std::vector<Enemy*> m_gameObjectsEnemies;

	// Static Camera permits target to have have class/struct/union/generic type
	static Camera2D* s_camera;

	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;


public:
	void StartGame();
	void RegisterGameObject(GameObject* agent);
	void UnregisterGameObject(GameObject* agent);
	static void UpdateCameraPosition(Vector2 playerPosition);
	static const float GetMapWidth() { return S_MAP_WIDTH; }
	static const float GetMapHeight() { return S_MAP_HEIGHT; }
	static float GetCameraHeight() { return S_CAMERA_HEIGHT / s_camera->zoom; }
	static float GetCameraWidth() { return S_CAMERA_WIDTH / s_camera->zoom; }
	static float GetCameraLeftLimit() { return s_camera->target.x - (S_CAMERA_WIDTH / 2) / s_camera->zoom; }
	static float GetCameraRightLimit() { return s_camera->target.x + (S_CAMERA_WIDTH / 2) / s_camera->zoom; }
	static float GetCameraTopLimit() { return s_camera->target.y - (S_CAMERA_HEIGHT / 2) / s_camera->zoom; }
	static float GetCameraBottomLimit() { return s_camera->target.y + (S_CAMERA_HEIGHT / 2) / s_camera->zoom; }
	static Vector2 GetCameraPosition() { return s_camera->target; }

private:
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects();
	void RenderGameObjects();
	void RemoveAgentsMarkedForRemoval();
};