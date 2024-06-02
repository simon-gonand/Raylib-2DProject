#include "Box2DPhysicsComponent.h"

#include "../../../Physics/Box2D/Box2DWorldManager.h"

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Shape* Shape, b2Vec2 Position, float Density, float Friction)
	: PhysicsComponent(InOwner)
{
	BodyDef = new b2BodyDef();
	BodyDef->type = Type;
	BodyDef->position = Position;
	Body = ((Box2DWorldManager*)Box2DWorldManager::Get(BOX2D).get())->CreateBody(BodyDef);
	BodyShape = Shape;
	FixtureDef = new b2FixtureDef();
	FixtureDef->shape = BodyShape;
	FixtureDef->density = Density;
	FixtureDef->friction = Friction;
	Fixture = Body->CreateFixture(FixtureDef);
}

Vector2 Box2DPhysicsComponent::GetWorldLocation() const
{
	b2Vec2 Position = Body->GetPosition();
	return { Position.x, Position.y};
}

void Box2DPhysicsComponent::Update(float Tick)
{
}
