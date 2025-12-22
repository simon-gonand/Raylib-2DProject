#include "Box2DWorldManager.h"

#include "Box2DDrawDebug.h"

#include "../../Helpers/Globals/Globals.h"

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

RaycastResult Box2DWorldManager::Raycast(Vector3 StartLocation, Vector3 EndLocation)
{
	FirstHitRaycastCallback* HitRaycastCallback = new FirstHitRaycastCallback();
	StartLocation = Vector3Scale(StartLocation,  1 / PTM_RATIO);
	EndLocation = Vector3Scale(EndLocation,  1 / PTM_RATIO);
	World->RayCast(HitRaycastCallback, b2Vec2{ StartLocation.x, StartLocation.y }, b2Vec2{ EndLocation.x, EndLocation.y });
	return HitRaycastCallback->Result;
}

float FirstHitRaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
{
	if (!fixture || !fixture->GetBody())
		return -1.0f;

	Result.bHasHit = true;
	Result.HitLocation = Vector3{ point.x, point.y };
	Result.HitLocation = Vector3Scale(Result.HitLocation, PTM_RATIO);
	Result.Normal = Vector3{ normal.x, normal.y };

	if(uintptr_t ptr = fixture->GetBody()->GetUserData().pointer)
		Result.HitActor = reinterpret_cast<Actor*>(ptr);

	return fraction;
}
