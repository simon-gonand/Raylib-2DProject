#include "Box2DWorldManager.h"

Box2DWorldManager::Box2DWorldManager()
{
}

void Box2DWorldManager::Initialize(Vector3 InGravity)
{
	b2Vec2 Gravity = b2Vec2(InGravity.x, InGravity.y);
	World = new b2World(Gravity);
}

void Box2DWorldManager::Update(float DeltaTime)
{
	World->Step(DeltaTime, 8, 3); // Velocity iterations and Position iterations values are set as advised on the Box2D doc
}

b2Body* Box2DWorldManager::CreateBody(const b2BodyDef* BodyDef)
{
	if (World) 
	{
		return World->CreateBody(BodyDef);
	}
	return nullptr;
}
