#pragma once
#include <cstdlib>
#include <list>
#include <vector>

class GameObject;
class Player;
class Enemy;

class Game
{
private: 
	// Private member
	static Game* s_instance;
	float m_deltatime;
	// Private constructor make sure it can't be called to create an instance
	Game();
public:
	static Game* GetInstance();

	// Destruction of the default copy constructor to not allow copy of this object
	Game(const Game& obj) = delete;

	~Game();


public:
	static bool s_gameRunning;

public:
	Player* m_player;
	// List that contain all the game object instanciate
	std::list<GameObject*> m_gameObjects;
	// List that contain all the game object Enemies - help for collision detection
	std::vector<Enemy*> m_gameObjectsEnemies;
	std::vector<GameObject*> m_gameObjectsToRemove;
private: 
	void Initialize();
	void HandleInput();
	void Update(float deltatime);
	void RenderScene();
	void Release();
	void RemoveGameObjectsMarkedForRemoval();


public:
	void Run();
	void RegisterGameObjects(GameObject* gameObject);
	void UnregisterGameObjects(GameObject* gameObject);

};