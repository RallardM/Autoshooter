#pragma once
#include <list>
#include <vector>

#include "raylib.h"

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

	static const float S_MAP_WIDTH;
	static const float S_MAP_HEIGHT;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = S_MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = S_MAP_HEIGHT / CELL_SIZE;

	Player* m_player;
	static Camera2D* s_camera;

	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;


public:
	void StartGame();
	void RegisterAgent(GameObject* agent);
	void UnregisterAgent(GameObject* agent);
	static void UpdateCameraPosition(Vector2 playerPosition);
	static const float GetMapWidth() { return S_MAP_WIDTH; }
	static const float GetMapHeight() { return S_MAP_HEIGHT; }

private:
	void MainLoop();
	void RenderBackground();
	void UpdateGameObjects();
	void RenderGameObjects();
	void RemoveAgentsMarkedForRemoval();
};