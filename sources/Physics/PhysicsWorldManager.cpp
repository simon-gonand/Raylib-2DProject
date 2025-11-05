#include "PhysicsWorldManager.h"
#include"Box2D/Box2DWorldManager.h"

#include <memory>

std::shared_ptr<PhysicsWorldManager> PhysicsWorldManager::Instance;

PhysicsWorldManager::PhysicsWorldManager()
{
}

std::shared_ptr<PhysicsWorldManager> PhysicsWorldManager::Get(PhysicsEngineType InPhysicsEngineType)
{
    if (!Instance)
    {
        switch (InPhysicsEngineType) 
        {
        case BOX2D:
            Instance = std::make_shared<Box2DWorldManager>();
        }
    }

    return Instance;
}

void PhysicsWorldManager::SetDebugMode(bool bInDebug)
{
    bDebugMode = bInDebug;
}
