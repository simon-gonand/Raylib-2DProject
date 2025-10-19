#include "Box2DPhysicsComponent.h"

#include "../../../Physics/Box2D/Box2DWorldManager.h"
#include <iostream>

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Shape* Shape, 
	const b2Vec2& Position, const float& Density, const float& Friction)
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

	BindEvents(InOwner);
}

Vector2 Box2DPhysicsComponent::GetWorldLocation() const
{
	b2Vec2 Position = Body->GetPosition();
	return { Position.x, Position.y};
}

Vector2 Box2DPhysicsComponent::GetLinearVelocity() const
{
	b2Vec2 Velocity = Body->GetLinearVelocity();
	return {Velocity.x, Velocity.y };
}

void Box2DPhysicsComponent::SetLinearVelocity(const Vector2& NewVelocity)
{
	Body->SetLinearVelocity({ NewVelocity.x, NewVelocity.y });
}

void Box2DPhysicsComponent::AddLinearVelocity(const Vector2& VelocityToAdd)
{
	b2Vec2 CurrentVelocity = Body->GetLinearVelocity();
	Body->SetLinearVelocity({ CurrentVelocity.x + VelocityToAdd.x, CurrentVelocity.y + VelocityToAdd.y });
}

void Box2DPhysicsComponent::Update(float Tick)
{
	if (GetOwner()) 
	{
		b2Vec2 Position = Body->GetPosition();
		GetOwner()->SetActorLocation({ Position.x, Position.y, 0.0f });
	}
}

void Box2DPhysicsComponent::BindEvents(std::shared_ptr<Actor> InOwner)
{
	InOwner->BindOnLocationSet<Box2DPhysicsComponent, &Box2DPhysicsComponent::OnOwnerLocationSet>(this);
	InOwner->BindOnRotationSet<Box2DPhysicsComponent, &Box2DPhysicsComponent::OnOwnerRotationSet>(this);
}

void Box2DPhysicsComponent::OnOwnerLocationSet(const Vector3& NewLocation)
{
	Body->SetTransform({ NewLocation.x, NewLocation.y }, Body->GetAngle());
}

void Box2DPhysicsComponent::OnOwnerRotationSet(const Quaternion& NewRotation)
{
	float Angle = std::acos(NewRotation.w) * 2;
	Body->SetTransform(Body->GetPosition(), Angle);
}
