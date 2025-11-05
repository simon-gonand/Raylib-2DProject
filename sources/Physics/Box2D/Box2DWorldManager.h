#pragma once

#include "../PhysicsWorldManager.h"

#include <box2d/box2d.h>

class Box2DWorldManager: public PhysicsWorldManager
{
private:
	b2World* World = nullptr;
	class Box2DDrawDebug* DebugDrawObj;

public:
	Box2DWorldManager();

	virtual void Initialize(const Vector3& InGravity) override;
	virtual void Update(float DeltaTime) override;

	virtual void DrawDebug() override;

	b2Body* CreateBody(const b2BodyDef* BodyDef);
};

