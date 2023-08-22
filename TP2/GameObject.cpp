#include <iostream>

#include "GameObject.h"
#include "Game.h"
#include "GameObjectPool.h"

unsigned short int GameObject::s_gameObjectId = 0;

GameObject::GameObject()
{
	m_gameObjectId = s_gameObjectId++;
	std::cout << "GameObject constructor called. ID = " << m_gameObjectId << std::endl;
}

GameObject::~GameObject()
{
	std::cout << "GameObject destructor called. ID = " << m_gameObjectId << std::endl;
}

const void GameObject::FollowPosition(Vector2& newPosition)
{
	m_position = newPosition;
}

void GameObject::OnStart()
{
	GameObjectPool::GetInstance()->RegisterGameObject(this);
}