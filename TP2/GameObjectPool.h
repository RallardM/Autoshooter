#pragma once
#include <list>
#include <vector>

#include "GameObject.h"

class GameObjectPool
{
	friend class Projectile;
	friend class CollisionManager;
	friend class GameObject;
	friend class Player;
	friend class Enemy;
	friend class ExperienceOrb;
	friend class Game;

public:
	~GameObjectPool();
	static GameObjectPool* GetInstance();

private:
	static GameObjectPool* _Instance;
	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;
	
private:
	GameObjectPool(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }
	void RegisterGameObject(GameObject* gameObject);
	void UnregisterGameObject(GameObject* gameObject);
	EGameObjectType GetGameObjectType(GameObject* gameObject);
	GameObject* GetClosestGameObject(const Vector2& position, const EGameObjectType& type);
	void UpdateGameObjects(const float& deltatime);
	unsigned short int GetActiveObjectCountFromList(const EGameObjectType& type);
	
	void RenderGameObjects();
	void ResetAllObjects();
	void UnegisterAllObjects();
	void RemoveAllGameObjects();
	void RemoveGameObjectsMarkedForRemoval();

	void IntializeEnemyPool();

	void CleanUpGame();
};

