#pragma once
#include "GameObject.h"
#include "GLOBALS.h"

class Entity : public GameObject
{
private:
    static unsigned short int s_entityId;

public:
    unsigned short int m_entityId = 0;

protected:
    short int m_health = HEALTH_VALUE;
    const unsigned short int MAX_HEALTH = MAX_HEATH_VALUE;

public: 
    Entity();
    virtual ~Entity() = 0;

    virtual const short int GetHealth() const = 0;
    virtual const short int GetMaxHealth() const = 0;
    virtual const EGameObjectType GetGameObjectType() const = 0;
};