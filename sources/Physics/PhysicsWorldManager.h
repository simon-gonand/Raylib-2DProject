#pragma once

#include "raymath.h"

#include <memory>

enum PhysicsEngineType 
{
	BOX2D
};

class PhysicsWorldManager
{
private:
	static std::shared_ptr<PhysicsWorldManager> Instance;

	PhysicsWorldManager(PhysicsWorldManager& InPhysicsWorldManager) = delete;
	void operator=(const PhysicsWorldManager& InPhysicsWorldManager) = delete;
	
protected:
	PhysicsWorldManager();

public:
	static std::shared_ptr<PhysicsWorldManager> Get(PhysicsEngineType InPhysicsEngineType);

	virtual void Initialize(const Vector3& InGravity) = 0;
	virtual void Update(float DeltaTime) = 0;
};

