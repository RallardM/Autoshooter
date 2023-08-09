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
	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 800;
	const float CELL_SIZE = 30.f;
	const float COLUMN_COUNT = SCREEN_WIDTH / CELL_SIZE;
	const float ROW_COUNT = SCREEN_HEIGHT / CELL_SIZE;

	Player* m_player;
	std::list<GameObject*> m_agents;
	std::vector<GameObject*> m_agentsToRemove;

public:
	void StartGame();
	void MainLoop();
	void RegisterAgent(GameObject* agent);
	void UnregisterAgent(GameObject* agent);
	static const int GetScreenWidth() { return SCREEN_WIDTH; }
	static const int GetScreenHeight() { return SCREEN_HEIGHT; }

private:
	void RenderBackground();
	void UpdateGameObjects();
	void RenderGameObjects();
	void RemoveAgentsMarkedForRemoval();
};