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
	const void InitializeGameObjects();
	
private: // Private methods
	GameObjectPool(); // Private constructor for singleton pattern https://youtu.be/PPup1yeU45I
	
	const void RegisterGameObject(GameObject* gameObject);
	const void UnregisterGameObject(GameObject* gameObject);
	const EGameObjectType GetGameObjectType(const GameObject* gameObject) const;
	GameObject* GetClosestGameObject(const Vector2& position, const EGameObjectType& type) const;
	const void UpdateGameObjects(const float& deltatime) const;
	const unsigned short int GetActiveObjectCountFromList(const EGameObjectType& type) const;
	
	const void RenderGameObjects() const;
	const void ResetAllObjects() const;
	const void UnegisterAllObjects();
	const void RemoveAllGameObjects();
	const void RemoveGameObjectsMarkedForRemoval();
	const void UpdateEnemySpawner() const;;
	const void CleanUpGame();

	const std::list<GameObject*> GetGameObjects() const { return m_gameObjects; }
	// Player getters // TODO Extract experience to its own class
	const Player* GetPlayer() const { return m_player; }
	const Vector2 GetPlayerPosition() const { return { m_player->m_position.x, m_player->m_position.y }; }
	const unsigned short int GetPlayerExperience() const { return m_player->m_experience; }
	const unsigned short int GetPlayerTotalExperience() const { return m_player->m_totalExperience; }
	const void AddPlayerExperience(unsigned short int experience) const { m_player->m_experience += experience; m_player->m_totalExperience += experience; }
};

