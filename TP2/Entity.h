#pragma once
#include "GameObject.h"

class Entity : public GameObject
{

protected:
    short int m_health = 100;
    const unsigned short int MAX_HEALTH = 100;

public: 
    virtual const short int GetHealth() const = 0;
    virtual const short int GetMaxHealth() const = 0;
    virtual const EGameObjectType GetGameObjectType() const = 0;
};

