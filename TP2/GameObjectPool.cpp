#include <iostream>

#include "GameObjectPool.h"
#include "MathUtils.h"
#include "CameraManager.h"
#include "Globals.h"

GameObjectPool* GameObjectPool::_Instance = nullptr;

GameObjectPool::~GameObjectPool()
{
}

GameObjectPool* GameObjectPool::GetInstance()
{
    if (_Instance == nullptr)
    {
        _Instance = new GameObjectPool();
    }
    return _Instance;
}

GameObjectPool::GameObjectPool()
{
	std::cout << "GameObjectPool created" << std::endl;
}

const void GameObjectPool::InitializeGameObjects()
{
	// Initialize random seed
	srand(static_cast<unsigned int>(time(NULL))); // cast for the warning :  C4244: 'argument': conversion from 'time_t' to 'unsigned int', possible loss of data

	// Initialize camera manager
	CameraManager* m_cameraManager = CameraManager::GetInstance();
	m_cameraManager->InitializeCamera();
	m_camera = m_cameraManager->GetCamera();

	// Initialize player
	m_player = new Player();
	m_player->OnStart();

	_Instance = this;
	InitWindow((int)m_cameraManager->GetCameraWidth(), (int)m_cameraManager->GetCameraHeight(), "raylib [core] example - basic window");
	SetTargetFPS(TARGET_FPS);
}

const void GameObjectPool::RegisterGameObject(GameObject* gameObject)
{
    m_gameObjects.push_back(gameObject);
    //std::cout << "GameObject added to gameObjects list. GameObjects amount: " << m_gameObjects.size() << std::endl;
}

const void GameObjectPool::UnregisterGameObject(GameObject* gameObject)
{
    m_gameObjectsToRemove.push_back(gameObject);
    //cout << "GameObject marked for removal" << endl;
}

const EGameObjectType GameObjectPool::GetGameObjectType(const GameObject* gameObject) const
{
    return gameObject->GetGameObjectType();
}

GameObject* GameObjectPool::GetClosestGameObject(const Vector2& position, const EGameObjectType& type) const
{
	GameObject* closest = nullptr;
	float closestDistance = 0.f;

	for (GameObject* gameObject : _Instance->m_gameObjects)
	{
		if (gameObject->GetGameObjectType() == type)
		{
			float distance = GetFloatDistanceBetweenTwoVects(position, gameObject->GetPosition());
			if (closest == nullptr || distance < closestDistance)
			{
				closest = gameObject;
				closestDistance = distance;
			}
		}
	}

	return closest;
}

const void GameObjectPool::UpdateGameObjects(const float& deltatime) const
{

	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		if (i->IsActive() == false)
		{
			continue;
		}

		i->Update(deltatime);
	}
}

const unsigned short int GameObjectPool::GetActiveObjectCountFromList(const EGameObjectType& type) const
{
	unsigned short int count = 0;
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		if (i->GetGameObjectType() == type && i->IsActive())
		{
			count++;
		}
	}

	return count;
}

const void GameObjectPool::RenderGameObjects() const
{
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		if (i->IsActive() == false)
		{
			continue;
		}

		i->Render();
	}
}

const void GameObjectPool::ResetAllObjects() const
{
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		i->Reset();
	}
}

const void GameObjectPool::UnegisterAllObjects()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject == nullptr) { continue; }

		// if not in m_gameObjectsToRemove push_back to m_gameObjectsToRemove
		if (std::find(m_gameObjectsToRemove.begin(), m_gameObjectsToRemove.end(), gameObject) == m_gameObjectsToRemove.end())
		{
			m_gameObjectsToRemove.push_back(gameObject);
		}

	}
}

const void GameObjectPool::RemoveAllGameObjects()
{
	for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
	{
		if (m_gameObjectsToRemove[i] == nullptr) { continue; }

		auto iter = std::remove(m_gameObjects.begin(), m_gameObjects.end(), m_gameObjectsToRemove[i]);
		m_gameObjects.erase(iter);

		delete m_gameObjectsToRemove[i];
		m_gameObjectsToRemove[i] = nullptr;
	}

	m_gameObjectsToRemove.clear();
	m_gameObjectsToRemove.resize(0);

	for (GameObject* obj : m_gameObjects)
	{
		if (obj == nullptr) { continue; }

		delete obj;
		obj = nullptr;
	}

	m_gameObjects.clear();
	m_gameObjects.resize(0);
}

const void GameObjectPool::RemoveGameObjectsMarkedForRemoval()
{
	for (int i = 0; i < m_gameObjectsToRemove.size(); i++)
	{
		if (m_gameObjectsToRemove[i] == nullptr) { continue; }
		if (m_gameObjectsToRemove[i]->IsActive() == true) { continue; }

		auto iter = std::remove(m_gameObjects.begin(), m_gameObjects.end(), m_gameObjectsToRemove[i]);
		m_gameObjects.erase(iter);

		delete m_gameObjectsToRemove[i];
		m_gameObjectsToRemove[i] = nullptr;
	}

	m_gameObjectsToRemove.clear();
	m_gameObjectsToRemove.resize(0);

	for (GameObject* obj : m_gameObjects)
	{
		if (obj == nullptr) { continue; }
		if (obj->IsActive() == true) { continue; }

		m_gameObjectsToRemove.push_back(obj);
	}
}

const void GameObjectPool::UpdateEnemySpawner() const
{
	EGameObjectType enemyType = EGameObjectType::ENEMY;
	unsigned short int enemiesCount = GameObjectPool::GetInstance()->GetActiveObjectCountFromList(enemyType);

	if (enemiesCount < MAX_ENEMY_AMOUNT_PER_LEVELS * m_player->GetLevel())
	{
		Enemy* enemy = new Enemy();

		enemy->OnStart();
	}
}

const void GameObjectPool::CleanUpGame()
{
	ResetAllObjects();
	UnegisterAllObjects();
	RemoveAllGameObjects();
}