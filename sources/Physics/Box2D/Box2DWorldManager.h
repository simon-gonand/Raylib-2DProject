#pragma once

#include "../PhysicsWorldManager.h"

#include <box2d/box2d.h>

float FirstHitRaycastCallback(b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context);

namespace Box2DDrawDebug
{
	void DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context);
	void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context);
	void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context);
	void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context);
	void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context);
	void DrawTransform(b2Transform transform, void* context);
	void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context);
	void DrawString(b2Vec2 p, const char* s, b2HexColor color, void* context);

	struct Color ConvertToColor(const b2HexColor& color);
};

class Box2DWorldManager: public PhysicsWorldManager
{
private:
	b2WorldId WorldId;
	b2DebugDraw DebugDraw;

public:
	Box2DWorldManager();

	virtual void Initialize(const Vector3& InGravity) override;
	virtual void Update(float DeltaTime) override;

	virtual void DrawDebug() override;

	b2BodyId CreateBody(const b2BodyDef* BodyDef, void* UserData = nullptr);

	virtual RaycastResult Raycast(Vector3 StartLocation, Vector3 EndLocation) override;
	virtual void* CreateDistanceJointBetween(std::shared_ptr<class PhysicsComponent> PhysicsCompA, std::shared_ptr<PhysicsComponent> PhysicsCompB, Vector3 AttachPointA, Vector3 AttachPointB) override;
	virtual void DestroyJoint(void* Joint) override;
};

