#include "Ground.h"
#include "../../Components/Physics/Box2D/Box2DPhysicsComponent.h"

void Ground::Initialize()
{
	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(100.0f, 10.0f);

	std::shared_ptr<Box2DPhysicsComponent> PhysicsComp = std::make_shared<Box2DPhysicsComponent>(shared_from_this(), b2_staticBody, &PhysicsShape);
	AddComponent(PhysicsComp);

	SetActorLocation({ 0.0f, -180.0f, 0.0f });
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ 200.0f, 20.0f });
}

void Ground::Draw(const Vector2& ScreenSize)
{
	Vector3 Scale = GetActorScale();
	Vector2 DrawLocation = GetLocationToDraw(ScreenSize);
	DrawRectangle(DrawLocation.x, DrawLocation.y, Scale.x, Scale.y, WHITE);
}
