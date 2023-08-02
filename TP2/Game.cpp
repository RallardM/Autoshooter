#include <iostream>

#include "Game.h"

//#include "Projectile.h"

using namespace std;

// Initializing instance ptr with NULL value 
Game* Game::s_instance = NULL;
bool Game::s_gameRunning = true;


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
    delete s_instance;
}

void Game::Initialize()
{
    InitWindow(WIDTH, HEIGHT, "Auto Shooter - V.0.01");
   
    RegisterGameObjects(m_player);
}


void Game::HandleInput()
{
    int keypressed = GetKeyPressed();

    if (IsKeyDown(KEY_W))
    {
        //Direction up
    }
    if (IsKeyDown(KEY_S))
    {
        //Direction down
    }
    if (IsKeyDown(KEY_A))
    {
        //Direction left
    }
    if (IsKeyDown(KEY_D))
    {
        //Direction right
    }

    if (WindowShouldClose())
    {
        Game::s_gameRunning = false;
    }

   

}

void Game::Update(float deltatime)
{
    /*
    if (!m_gameObjects.empty())
    {
        std::list<GameObject*>::iterator it;
        for (it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
        {
            (*it)->Update(deltatime);
        }
    }
    */
}


void Game::RenderScene()
{
    if (!m_gameObjects.empty())
    {
        std::list<GameObject*>::iterator it;
        for (it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
        {
            (*it)->Render();
        }
    }
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
        HandleInput();
        Update(GetFrameTime());
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
