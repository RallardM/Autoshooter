#pragma once
#include "GameObject.h"
#include "GLOBALS.h"

/**
 * @brief Abstract class that represent our game element
*/
class Entity : public GameObject
{

protected:
    short int m_health = HEALTH_VALUE;
    const unsigned short int MAX_HEALTH = MAX_HEATH_VALUE;

public: 
    /**
     * @brief Abstract Method that get entity health
     * @return health of the entity
    */
    virtual const short int GetHealth() const = 0;
    /**
     * @brief Abstract method that get entity max health
     * @return max Health of the entity
    */
    virtual const short int GetMaxHealth() const = 0;
    /**
     * @brief Abstract method that get game object type
     * @return EGameObjectType type of game object
    */
    virtual const EGameObjectType GetGameObjectType() const = 0;
};

