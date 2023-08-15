#include <iostream>
#include "Entity.h"

unsigned short int Entity::s_entityId = 0;

Entity::Entity()
{
	m_entityId = s_entityId++;
	std::cout << "Entity constructor called. ID = " << m_entityId << std::endl;
}

Entity::~Entity()
{
	std::cout << "Entity destructor called. ID = " << m_entityId << std::endl;
}
