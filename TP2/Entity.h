#pragma once
#include "GameObject.h"
#include "Globals.h"

class Entity : public GameObject
{
private:
    static unsigned short int s_entityId;

public:
    unsigned short int m_entityId = 0;

protected:
    short int m_health = ENTITY_DEFAULT_HEALTH;
    const unsigned short int MAX_HEALTH = ENTITY_DEFAULT_HEALTH;

public: 
    Entity();
    virtual ~Entity() = 0;

    virtual const short int GetHealth() const = 0;
    virtual const short int GetMaxHealth() const = 0;
    virtual const EGameObjectType GetGameObjectType() const = 0;
};