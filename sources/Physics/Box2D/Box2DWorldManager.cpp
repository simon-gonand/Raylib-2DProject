#include "Box2DWorldManager.h"

#include "../../Helpers/Globals/Globals.h"

#include "../../Components/Physics/Box2D/Box2DPhysicsComponent.h"

#include <box2d/base.h>
#include <iostream>

Box2DWorldManager::Box2DWorldManager()
{
}

void Box2DWorldManager::Initialize(const Vector3& InGravity)
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	b2Vec2 Gravity = b2Vec2({ InGravity.x, InGravity.y });
	worldDef.gravity = Gravity;

	DebugDraw = b2DefaultDebugDraw();
	DebugDraw.drawShapes = true;
	DebugDraw.drawMass = true;
	DebugDraw.drawJoints = true;
	DebugDraw.DrawPolygonFcn = &Box2DDrawDebug::DrawPolygon;
	DebugDraw.DrawSolidPolygonFcn = &Box2DDrawDebug::DrawSolidPolygon;
	DebugDraw.DrawCircleFcn = &Box2DDrawDebug::DrawCircle;
	DebugDraw.DrawSolidCircleFcn = &Box2DDrawDebug::DrawSolidCircle;
	DebugDraw.DrawSegmentFcn = &Box2DDrawDebug::DrawSegment;
	DebugDraw.DrawTransformFcn = &Box2DDrawDebug::DrawTransform;
	DebugDraw.DrawPointFcn = &Box2DDrawDebug::DrawPoint;
	DebugDraw.DrawStringFcn = &Box2DDrawDebug::DrawString;

	WorldId = b2CreateWorld(&worldDef);
}

void Box2DWorldManager::Update(float DeltaTime)
{
	b2World_Step(WorldId, 1.0f / 60.0f, 4); // Velocity iterations and Position iterations values are set as advised on the Box2D doc
	b2SensorEvents sensorEvents = b2World_GetSensorEvents(WorldId);
	for (int i = 0; i < sensorEvents.beginCount; ++i)
	{
		b2SensorBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
		Box2DPhysicsComponent* SensorPhysicsComp = reinterpret_cast<Box2DPhysicsComponent*>(b2Shape_GetUserData(beginTouch->sensorShapeId));
		Box2DPhysicsComponent* VisitorPhysicsComp = reinterpret_cast<Box2DPhysicsComponent*>(b2Shape_GetUserData(beginTouch->visitorShapeId));
		SensorPhysicsComp->BroadcastOnBeginOverlap(VisitorPhysicsComp);
	}
	for (int i = 0; i < sensorEvents.endCount; ++i)
	{
		b2SensorEndTouchEvent* endTouch = sensorEvents.endEvents + i;
		if (b2Shape_IsValid(endTouch->visitorShapeId))
		{
			Box2DPhysicsComponent* SensorPhysicsComp = reinterpret_cast<Box2DPhysicsComponent*>(b2Shape_GetUserData(endTouch->sensorShapeId));
			Box2DPhysicsComponent* VisitorPhysicsComp = reinterpret_cast<Box2DPhysicsComponent*>(b2Shape_GetUserData(endTouch->visitorShapeId));
			SensorPhysicsComp->BroadcastOnEndOverlap(VisitorPhysicsComp);
		}
	}
}

void Box2DWorldManager::DrawDebug()
{
	if (bDebugMode)
		b2World_Draw(WorldId, &DebugDraw);
}

b2BodyId Box2DWorldManager::CreateBody(const b2BodyDef* BodyDef, void* UserData)
{
	b2BodyId BodyId = b2CreateBody(WorldId, BodyDef);
	b2Body_SetUserData(BodyId, UserData);
	return BodyId;
}

RaycastResult Box2DWorldManager::Raycast(Vector3 StartLocation, Vector3 EndLocation)
{
	RaycastResult HitRaycastResult;
	StartLocation = Vector3Scale(StartLocation,  1 / PTM_RATIO);
	EndLocation = Vector3Scale(EndLocation,  1 / PTM_RATIO);
	b2RayResult Result = b2World_CastRayClosest(WorldId, b2Vec2({ StartLocation.x, StartLocation.y }), b2Vec2({ EndLocation.x - StartLocation.x, EndLocation.y - StartLocation.y }), b2DefaultQueryFilter());
	HitRaycastResult.bHasHit = Result.hit;
	HitRaycastResult.HitLocation = Vector3Scale(Vector3{Result.point.x, Result.point.y}, PTM_RATIO);
	if (!B2_IS_NULL(Result.shapeId))
	{
		b2BodyId BodyId = b2Shape_GetBody(Result.shapeId);
		if (!B2_IS_NULL(b2Shape_GetBody(Result.shapeId)))
		{
			if (void* ptr = b2Body_GetUserData(BodyId))
				HitRaycastResult.HitActor = reinterpret_cast<Actor*>(ptr);
		}
	}

	HitRaycastResult.Normal = Vector3{ Result.normal.x, Result.normal.y };
	return HitRaycastResult;
}

int Box2DWorldManager::CreateDistanceJointBetween(std::shared_ptr<PhysicsComponent> PhysicsCompA, std::shared_ptr<PhysicsComponent> PhysicsCompB, Vector3 AttachPointA, Vector3 AttachPointB)
{
	std::shared_ptr<Box2DPhysicsComponent> Box2DPhysicsCompA = std::dynamic_pointer_cast<Box2DPhysicsComponent>(PhysicsCompA);
	std::shared_ptr<Box2DPhysicsComponent> Box2DPhysicsCompB = std::dynamic_pointer_cast<Box2DPhysicsComponent>(PhysicsCompB);

	if (!Box2DPhysicsCompA || !Box2DPhysicsCompB)
		return -1;

	b2BodyId BodyA = Box2DPhysicsCompA->GetBody();
	b2BodyId BodyB = Box2DPhysicsCompB->GetBody();
	b2Vec2 B2WorldAttachPointA = { AttachPointA.x / PTM_RATIO, AttachPointA.y / PTM_RATIO };
	b2Vec2 B2WorldAttachPointB = { AttachPointB.x / PTM_RATIO, AttachPointB.y / PTM_RATIO };
	b2Vec2 B2LocalAttachPointA = b2Body_GetLocalPoint(BodyA, B2WorldAttachPointA);
	b2Vec2 B2LocalAttachPointB = b2Body_GetLocalPoint(BodyB, B2WorldAttachPointB);

	b2DistanceJointDef JointDef = b2DefaultDistanceJointDef();
	JointDef.bodyIdA = BodyA;
	JointDef.bodyIdB = BodyB;
	JointDef.localAnchorA = B2LocalAttachPointA;
	JointDef.localAnchorB = B2LocalAttachPointB;
	JointDef.length = b2Distance(B2WorldAttachPointA, B2WorldAttachPointB);
	JointDef.collideConnected = true;

	unsigned int Id = NextAvailableJointId;
	++NextAvailableJointId;
	JointIds.insert({ Id, b2CreateDistanceJoint(WorldId, &JointDef) });

	return Id;
}

void Box2DWorldManager::DestroyJoint(int Joint)
{
	std::unordered_map<unsigned int, b2JointId>::iterator B2Joint = JointIds.find(Joint);
	if(B2Joint != JointIds.end())
		b2DestroyJoint(B2Joint->second);
}

float FirstHitRaycastCallback(b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context)
{
	if (B2_IS_NULL(shapeId) || !context)
		return -1.0f;

	RaycastResult* Result = reinterpret_cast<RaycastResult*>(context);

	b2BodyId BodyId = b2Shape_GetBody(shapeId);
	if (B2_IS_NULL(b2Shape_GetBody(shapeId)))
		return 1.0f;

	Result->bHasHit = true;
	Result->HitLocation = Vector3{ point.x, point.y };
	Result->HitLocation = Vector3Scale(Result->HitLocation, PTM_RATIO);
	Result->Normal = Vector3{ normal.x, normal.y };

	if(void* ptr = b2Body_GetUserData(BodyId))
		Result->HitActor = reinterpret_cast<Actor*>(ptr);

	return fraction;
}

void Box2DDrawDebug::DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context)
{
	for (int i = 0; i < vertexCount; i++) {
		b2Vec2 StartVertex = vertices[i] + transform.p;
		b2Vec2 EndVertex = i == vertexCount - 1 ? vertices[0] : vertices[i + 1];
		EndVertex += transform.p;
		DrawLineEx({ StartVertex.x * PTM_RATIO, StartVertex.y * PTM_RATIO }, { EndVertex.x * PTM_RATIO, EndVertex.y * PTM_RATIO }, 1.0f, ConvertToColor(color));
	}
}

void Box2DDrawDebug::DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context)
{
	for (int i = 0; i < vertexCount; i++) {
		b2Vec2 StartVertex = vertices[i];
		b2Vec2 EndVertex = i == vertexCount - 1 ? vertices[0] : vertices[i + 1];
		DrawLineEx({ StartVertex.x * PTM_RATIO, StartVertex.y * PTM_RATIO }, { EndVertex.x * PTM_RATIO, EndVertex.y * PTM_RATIO }, 1.0f, ConvertToColor(color));
	}
}

void Box2DDrawDebug::DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context)
{
	Box2DDrawDebug::DrawCircle(transform.p, radius, color, context);
}

void Box2DDrawDebug::DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context)
{
	DrawCircleV({ center.x * PTM_RATIO, center.y * PTM_RATIO }, radius * PTM_RATIO, ConvertToColor(color));
}

void Box2DDrawDebug::DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context)
{
	Vector2 P1 = { p1.x * PTM_RATIO, p1.y * PTM_RATIO };
	Vector2 P2 = { p2.x * PTM_RATIO, p2.y * PTM_RATIO };
	DrawLineEx(P1, P2, 2.0f, ConvertToColor(color));
}

void Box2DDrawDebug::DrawTransform(b2Transform transform, void* context)
{
	DrawCircleV({ transform.p.x * PTM_RATIO, transform.p.y * PTM_RATIO }, 1.5f, ORANGE);
}

void Box2DDrawDebug::DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context)
{
	DrawCircleV({ p.x * PTM_RATIO, p.y * PTM_RATIO }, 1.5f, ConvertToColor(color));
}

void Box2DDrawDebug::DrawString(b2Vec2 p, const char* s, b2HexColor color, void* context)
{
	DrawText(s, p.x * PTM_RATIO, p.y * PTM_RATIO, 10, ConvertToColor(color));
}

Color Box2DDrawDebug::ConvertToColor(const b2HexColor& color)
{
	Color DrawColor = GetColor(color);

	return DrawColor;
}
