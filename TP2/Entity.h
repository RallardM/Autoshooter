#pragma once
#include "GameObject.h"
#include "Globals.h"

class Entity : public GameObject
{
protected: // Protected member variables
    short int m_health = ENTITY_DEFAULT_HEALTH;
    const unsigned short int MAX_HEALTH = ENTITY_DEFAULT_HEALTH;

public:  // Public member variables
    unsigned short int m_entityId = 0;

private: // Private member variables
    static unsigned short int s_entityId;

public: // Public methods
    Entity();
    virtual ~Entity() = 0;

    virtual const short int GetHealth() const = 0;
    virtual const short int GetMaxHealth() const = 0;
    virtual const EGameObjectType GetGameObjectType() const = 0;

private: // Private methods

};