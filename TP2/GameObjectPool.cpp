#include "GameObjectPool.h"
#include "MathUtils.h"

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

void GameObjectPool::IntializeEnemyPool()
{
}


GameObjectPool::GameObjectPool()
{
}

void GameObjectPool::RegisterGameObject(GameObject* gameObject)
{
    m_gameObjects.push_back(gameObject);
    //std::cout << "GameObject added to gameObjects list. GameObjects amount: " << m_gameObjects.size() << std::endl;
}

void GameObjectPool::UnregisterGameObject(GameObject* gameObject)
{
    m_gameObjectsToRemove.push_back(gameObject);
    //cout << "GameObject marked for removal" << endl;
}

EGameObjectType GameObjectPool::GetGameObjectType(GameObject* gameObject)
{
    return gameObject->GetGameObjectType();
}

GameObject* GameObjectPool::GetClosestGameObject(const Vector2& position, const EGameObjectType& type)
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

void GameObjectPool::UpdateGameObjects(const float& deltatime)
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

unsigned short int GameObjectPool::GetActiveObjectCountFromList(const EGameObjectType& type)
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

void GameObjectPool::RenderGameObjects()
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

void GameObjectPool::ResetAllObjects()
{
	for (auto const& i : m_gameObjects)
	{
		if (i == NULL) { continue; }

		i->Reset();
	}
}

void GameObjectPool::UnegisterAllObjects()
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

void GameObjectPool::RemoveAllGameObjects()
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

void GameObjectPool::RemoveGameObjectsMarkedForRemoval()
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

void GameObjectPool::CleanUpGame()
{
	ResetAllObjects();
	UnegisterAllObjects();
	RemoveAllGameObjects();
}