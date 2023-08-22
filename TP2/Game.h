#pragma once

#include "MenuManager.h"
#include "CameraManager.h"

class Game
{
	
	friend class Player;

public:  // Public member variables

private: // Private member variables
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

public: // Public methods
	~Game();
	void MainLoop();
	static Game* GetInstance();

private: // Private methods
	Game(); // Private constructor for singleton pattern
	void RenderBackground();

	// Game getters and setters
	bool const IsPaused() const { return m_isPaused; }
	const void PauseGame() { m_isPaused = !m_isPaused; }

	// Map getters
	const float GetMapWidth() { return MAP_WIDTH; }
	const float GetMapHeight() { return MAP_HEIGHT; }
};