#include "Ground.h"

#include "../../Components/Physics/Box2D/Box2DPhysicsComponent.h"
#include "../../Helpers/Globals/Globals.h"
#include "../../Components/Renderer/2DRenderer/Renderer2DComponent.h"

void Ground::Initialize()
{
	Vector2 ScaleSizeMeter({ 20.0f, 1.0f });
	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(ScaleSizeMeter.x, ScaleSizeMeter.y);

    PhysicsComp = std::make_shared<Box2DPhysicsComponent>(shared_from_this(), b2_staticBody, &PhysicsShape);
	AddComponent(PhysicsComp);

    RendererComp = std::make_shared<Renderer2DComponent>(shared_from_this(), "");
    AddComponent(RendererComp);

	SetActorLocation({ 0.0f, 0.0f, 0.0f });
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ ScaleSizeMeter.x * 2 * PTM_RATIO, ScaleSizeMeter.y * 2 * PTM_RATIO });
}