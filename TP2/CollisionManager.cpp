#include <raylib.h>
#include "CollisionManager.h"


CollisionManager* CollisionManager::_Instance = 0;

CollisionManager::~CollisionManager()
{

}

CollisionManager* CollisionManager::GetInstance()
{
    if (_Instance == nullptr || NULL)
    {
        _Instance = new CollisionManager();
    }
    return _Instance;
}
