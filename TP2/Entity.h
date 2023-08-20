#pragma once
#include "GameObject.h"

class Entity : public GameObject
{
private:
    static unsigned short int s_entityId;

public:
    unsigned short int m_entityId = 0;

protected:
    short int m_health = 100;
    const unsigned short int MAX_HEALTH = 100;

public: 
    Entity();
    virtual ~Entity() = 0;

    virtual const short int GetHealth() const = 0;
    virtual const short int GetMaxHealth() const = 0;
    virtual const EGameObjectType GetGameObjectType() const = 0;
    virtual const bool GetIsSetToDestroy() const = 0;
    virtual void DestroyUIElements() = 0;
};