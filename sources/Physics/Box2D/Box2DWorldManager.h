#pragma once

#include "../PhysicsWorldManager.h"

#include <box2d/box2d.h>

class Box2DWorldManager: public PhysicsWorldManager
{
private:
	b2World* World = nullptr;

public:
	Box2DWorldManager();

	virtual void Initialize(Vector3 InGravity) override;
	virtual void Update(float DeltaTime) override;

	b2Body* CreateBody(const b2BodyDef* BodyDef);
};

