#include "Game.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

// Initializing instance ptr with NULL value 
Game* Game::s_instance = NULL;
bool Game::s_gameRunning = true;
Camera2D* Game::s_camera = nullptr;

/*
* GetInstance is a static method that returns an instance of Game class when it is invoked.
* It returns the same instance if it is inovked more than once as an instance
* of Game class is already created.
* @return s_instance: - pointer to an instance of the Game class
*/
Game* Game::GetInstance()
{
	if (s_instance == nullptr || NULL)
	{
		s_instance = new Game();
	}
	return s_instance;
}
// Default constuctor
Game::Game()
{
	m_player = new Player();
};

/*
* Destructor of game class that destroy the ptr to the unique instance of Game class and free
* occupied memory by the ptr
*/
Game::~Game()
{
	//delete m_player;
	if (!m_gameObjectsEnemies.empty())
	{
		m_gameObjectsEnemies.clear();
	}

	if (!m_gameObjects.empty())
	{
		std::list<GameObject*>::iterator it;
		for (it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			delete (*it);
		}
	}

	// delete s_camera
	delete s_camera;
}

void Game::Initialize()
{
	// Setting the seed for random number generation
	std::srand(std::time(NULL));

	// Initializing the camera
	s_camera = new Camera2D();
	s_camera->offset = { (float)WIDTH / 2, (float)HEIGHT / 2 };
	s_camera->rotation = 0.0f;
	s_camera->zoom = 0.8f;
	m_deltatime = GetFrameTime();

	//-- Creation of Enemies between min and max
	int enemyAmount = std::rand() % (MAX_ENEMY_AMOUNT - MIN_ENEMY_AMOUNT) + MIN_ENEMY_AMOUNT;

	for (int i = 0; i < enemyAmount; i++)// just for test 
	{
		m_gameObjectsEnemies.emplace_back(new Enemy());
	}
	//--
	// 
	//-- Updating the game object list with enemies and player

	if (!m_gameObjectsEnemies.empty())
	{
		for (int i = 0; i != m_gameObjectsEnemies.size(); ++i)
		{
			m_gameObjectsEnemies[i]->OnStart();
		}
	}

	m_player->OnStart();
	//--

	//-- Initialise game window throw raylib library
	InitWindow(WIDTH, HEIGHT, "Auto Shooter - V.0.01");
}


void Game::HandleInput()
{

	if (WindowShouldClose())
	{
		Game::s_gameRunning = false;
	}

	m_player->HandleInput();

}

void Game::Update(float deltatime)
{
	// Update every game object
	if (!m_gameObjects.empty())
	{
		std::list<GameObject*>::iterator it;
		for (it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			if (!(*it)->m_isDie)
			{
				Enemy* enemy = dynamic_cast<Enemy*>((*it));
				if (enemy != NULL)
				{
					enemy->Update(deltatime);
					enemy->Track(m_player->m_position.x, m_player->m_position.y);
				}
				else
				{
					(*it)->Update(deltatime);
				}

			}
		}
	}

}


void Game::RenderScene()
{
	BeginDrawing();

	ClearBackground(DARKGRAY);

	// Render grid
	// Source : Cours Algebre Vectoriel
	Color gridColor = GOLD;
	for (int i = 0; i < COLUMN_COUNT; ++i)
	{
		// Alternate grid color on even columns
		if (i % 2 == 0)
		{
			gridColor = SKYBLUE;
		}
		else
		{
			gridColor = GOLD;
		}

		Vector2 start = { CELL_SIZE * i, 0.f };
		Vector2 end = { CELL_SIZE * i, MAP_HEIGHT };
		DrawLineV(start, end, gridColor);
	}

	for (int i = 0; i < ROW_COUNT; ++i)
	{
		// Alternate grid color on even rows
		if (i % 2 == 0)
		{
			gridColor = SKYBLUE;
		}
		else
		{
			gridColor = GOLD;
		}

		Vector2 start = { 0.f, CELL_SIZE * i };
		Vector2 end = { MAP_WIDTH, CELL_SIZE * i };
		DrawLineV(start, end, gridColor);
	}

	// Render every game object
	if (!m_gameObjects.empty())
	{
		std::list<GameObject*>::iterator it;
		for (it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			if (!(*it)->m_isDie)
			{
				(*it)->Render();
			}
		}
	}

	EndDrawing();
}

void Game::Release()
{
	CloseWindow();
}




void Game::Run()
{
	Initialize();
	while (Game::s_gameRunning)
	{
		m_deltatime = GetFrameTime();
		HandleInput();
		Update(m_deltatime);
		RenderScene();
	}
	Release();
}
//Complicated way of removing agents, only to be sure that we do it AFTER
	//updating every agent in a frame

void Game::RemoveGameObjectsMarkedForRemoval()
{

	for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
	{
		m_gameObjects.remove(m_gameObjectsToRemove[i]);
		delete(m_gameObjectsToRemove[i]);
		std::cout << "Agent removed from agents list. Agents amount: " << m_gameObjects.size() << std::endl;
	}
	m_gameObjectsToRemove.clear();
	m_gameObjectsToRemove.resize(0);

}



void Game::RegisterGameObjects(GameObject* gameObject)
{
	m_gameObjects.push_back(gameObject);
	std::cout << "Agent added to agents list. Agents amount: " << m_gameObjects.size() << std::endl;
}

void Game::UnregisterGameObjects(GameObject* gameObject)
{
	m_gameObjectsToRemove.push_back(gameObject);
	cout << "Agent marked for removal" << endl;
}

void Game::UpdateCameraPosition(Vector2 playerPosition)
{
	s_camera->target = { playerPosition.x, playerPosition.y };
}
