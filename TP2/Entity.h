#pragma once
#include "GameObject.h"

class Entity : public GameObject
{

protected:
    short int m_health = 100;

public: 
    virtual const short int GetHealth() const { return m_health; }
};

