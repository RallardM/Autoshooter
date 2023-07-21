#pragma once
#include <list>
#include <vector>

#include "raylib.h"

class Agent;
class MainCharacter;

class Game
{
	static Game* _Instance;

public:
	static Game* GetInstance() { return _Instance; } //Not a real singleton written like this
	//This should be adressed

public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 450;

private:
	MainCharacter* m_mainCharacter;
	std::list<Agent*> m_agents;
	std::vector<Agent*> m_agentsToRemove;

public:
	void StartGame();
	void MainLoop();
	void RegisterAgent(Agent* agent);
	void UnregisterAgent(Agent* agent);
private:
	void UpdateAgents();
	void RemoveAgentsMarkedForRemoval();
};