#include "Ground.h"
#include "../../Components/Physics/Box2D/Box2DPhysicsComponent.h"
#include "../../Helpers/Globals/Globals.h"

void Ground::Initialize()
{
	Vector2 ScaleSizeMeter({ 10.0f, 1.0f });
	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(ScaleSizeMeter.x, ScaleSizeMeter.y);

	std::shared_ptr<Box2DPhysicsComponent> PhysicsComp = std::make_shared<Box2DPhysicsComponent>(shared_from_this(), b2_staticBody, &PhysicsShape);
	AddComponent(PhysicsComp);

	SetActorLocation({ 0.0f, 0.0f, 0.0f });
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ ScaleSizeMeter.x * 2 * PTM_RATIO, ScaleSizeMeter.y * 2 * PTM_RATIO });
}

void Ground::Draw(const Vector2& ScreenSize)
{
    Vector3 Scale = GetActorScale();
    Vector3 DrawLocation = GetActorLocation();

    Rectangle rect = {
        DrawLocation.x,
        DrawLocation.y,
        Scale.x,
        Scale.y
    };

    DrawRectanglePro(rect, { Scale.x / 2, Scale.y / 2 }, 0.0f, WHITE);
}
