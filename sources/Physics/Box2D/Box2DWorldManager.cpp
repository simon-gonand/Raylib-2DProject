#include "Box2DWorldManager.h"

#include "Box2DDrawDebug.h"

Box2DWorldManager::Box2DWorldManager()
{
}

void Box2DWorldManager::Initialize(const Vector3& InGravity)
{
	b2Vec2 Gravity = b2Vec2(InGravity.x, InGravity.y);
	World = new b2World(Gravity);

	DebugDrawObj = new Box2DDrawDebug();
	DebugDrawObj->SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
	World->SetDebugDraw(DebugDrawObj);
}

void Box2DWorldManager::Update(float DeltaTime)
{
	World->Step(DeltaTime, 8, 3); // Velocity iterations and Position iterations values are set as advised on the Box2D doc
}

void Box2DWorldManager::DrawDebug()
{
	if (bDebugMode)
		World->DebugDraw();
}

b2Body* Box2DWorldManager::CreateBody(const b2BodyDef* BodyDef)
{
	if (World) 
	{
		return World->CreateBody(BodyDef);
	}
	return nullptr;
}
