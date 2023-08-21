#pragma once
#include "GameObject.h"
#include "Entity.h"
#include "Globals.h"
#include "Enumerations.h"

class Entity;

struct SUIElementData
{
public:
    Entity* TARGET = nullptr;
	Color COLOR;
    Vector2 BAR_SIZE;
    Vector2 OFFSET;
    float FLOAT_VALUE;
    int FONT_SIZE;
    unsigned short int UIELEMENT_TYPE; // Visual Studio did not compiled the Enum Class here except if converted to a unsigned short int
    unsigned short int INT_VALUE;
    bool HAS_SECONDARY_BAR;
    SUIElementData() = default;
    SUIElementData(Entity* entity, unsigned short int UiElementType, Color color, Vector2 barSize, Vector2 offset, float floatValue, unsigned short int intValue, int fontSize, bool hasSecondryBar)
		: TARGET(entity),UIELEMENT_TYPE(UiElementType), COLOR(color), BAR_SIZE(barSize), OFFSET(offset), FLOAT_VALUE(floatValue), INT_VALUE(intValue), FONT_SIZE(fontSize), HAS_SECONDARY_BAR(hasSecondryBar)
	{
	}
};

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