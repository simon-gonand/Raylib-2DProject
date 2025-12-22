#include "PhysicsWorldManager.h"
#include"Box2D/Box2DWorldManager.h"

#include <memory>

std::shared_ptr<PhysicsWorldManager> PhysicsWorldManager::Instance;
PhysicsEngineType PhysicsWorldManager::EngineType;

PhysicsWorldManager::PhysicsWorldManager()
{
}

void PhysicsWorldManager::SetPhysicsEngineType(PhysicsEngineType InEngineType)
{
    EngineType = InEngineType;
}

std::shared_ptr<PhysicsWorldManager> PhysicsWorldManager::Get()
{
    if (!Instance)
    {
        switch (EngineType)
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
