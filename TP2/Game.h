#pragma once


//#include "Player.h"
#include "MenuManager.h"
#include "CameraManager.h"

//class GameObject;
//class Player;

class Game
{
	
	friend class Player;

public:
	static Game* GetInstance();

private:
	const float MAP_WIDTH = 1601.0f;
	const float MAP_HEIGHT = 1601.0f;
	const float CELL_SIZE = 16.0f;
	const float COLUMN_COUNT = MAP_WIDTH / CELL_SIZE;
	const float ROW_COUNT = MAP_HEIGHT / CELL_SIZE;
	bool m_isPaused = false;

	// Keep dynamically changing sizes bellow
	static Game* _Instance;
	CameraManager* m_cameraManager = nullptr;
	MenuManager* m_menuManager = nullptr;

public:
	~Game();
	void MainLoop();

private:
	Game(); // Private constructor for singleton pattern
	void RenderBackground();

	// Game getters and setters
	bool const IsPaused() const { return m_isPaused; }
	void PauseGame() { m_isPaused = !m_isPaused; }

	// Map getters
	const float GetMapWidth() { return MAP_WIDTH; }
	const float GetMapHeight() { return MAP_HEIGHT; }
};