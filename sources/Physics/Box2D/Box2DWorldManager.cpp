#include "Box2DWorldManager.h"

#include "Box2DDrawDebug.h"

#include "../../Helpers/Globals/Globals.h"

#include "../../Components/Physics/Box2D/Box2DPhysicsComponent.h"

Box2DWorldManager::Box2DWorldManager()
{
}

void Box2DWorldManager::Initialize(const Vector3& InGravity)
{
	b2Vec2 Gravity = b2Vec2(InGravity.x, InGravity.y);
	World = new b2World(Gravity);

	DebugDrawObj = new Box2DDrawDebug();
	DebugDrawObj->SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit | b2Draw::e_jointBit);
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

void* Box2DWorldManager::CreateDistanceJointBetween(std::shared_ptr<PhysicsComponent> PhysicsCompA, std::shared_ptr<PhysicsComponent> PhysicsCompB, const Vector3& AttachPointA, const Vector3& AttachPointB)
{
	std::shared_ptr<Box2DPhysicsComponent> Box2DPhysicsCompA = std::dynamic_pointer_cast<Box2DPhysicsComponent>(PhysicsCompA);
	std::shared_ptr<Box2DPhysicsComponent> Box2DPhysicsCompB = std::dynamic_pointer_cast<Box2DPhysicsComponent>(PhysicsCompB);

	if (!Box2DPhysicsCompA || !Box2DPhysicsCompB)
		return nullptr;

	b2Body* BodyA = Box2DPhysicsCompA->GetBody();
	b2Body* BodyB = Box2DPhysicsCompB->GetBody();
	b2Vec2 B2WorldAttachPointA = { AttachPointA.x / PTM_RATIO, AttachPointA.y / PTM_RATIO };
	b2Vec2 B2WorldAttachPointB = { AttachPointB.x / PTM_RATIO, AttachPointB.y / PTM_RATIO };
	b2Vec2 B2LocalAttachPointA = BodyA->GetLocalPoint(B2WorldAttachPointA);
	b2Vec2 B2LocalAttachPointB = BodyB->GetLocalPoint(B2WorldAttachPointB);

	b2DistanceJointDef JointDef = b2DistanceJointDef();
	JointDef.Initialize(BodyA, BodyB, B2WorldAttachPointA, B2WorldAttachPointB);
	JointDef.collideConnected = true;

	return World->CreateJoint(&JointDef);
}

void Box2DWorldManager::DestroyJoint(void* Joint)
{
	b2Joint* B2Joint = static_cast<b2Joint*>(Joint);
	if(B2Joint)
		World->DestroyJoint(B2Joint);
	Joint = nullptr;
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
