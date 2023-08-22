#pragma once
#include <list>
#include <vector>

#include "GameObject.h"
#include "Player.h"

class GameObjectPool
{
	friend class Projectile;
	friend class CollisionManager;
	friend class GameObject;
	friend class Player;
	friend class Enemy;
	friend class ExperienceOrb;
	friend class Game;
	friend class CameraManager;
	friend class UIElement;

public:  // Public member variables

private: // Private member variables
	static GameObjectPool* _Instance;
	std::list<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_gameObjectsToRemove;
	Camera2D* m_camera = nullptr;
	Player* m_player = nullptr;

public: // Public methods
	~GameObjectPool();
	static GameObjectPool* GetInstance();
	void InitializeGameObjects();
	
private: // Private methods
	GameObjectPool(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	
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
	void UpdateEnemySpawner();
	void IntializeEnemyPool();
	void CleanUpGame();

	std::list<GameObject*> GetGameObjects() { return m_gameObjects; }
	// Player getters // TODO Extract experience to its own class
	Player* GetPlayer() { return m_player; }
	Vector2 GetPlayerPosition() { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() { return m_player->m_totalExperience; }
	void AddPlayerExperience(unsigned short int experience) { m_player->m_experience += experience; m_player->m_totalExperience += experience; }
};

