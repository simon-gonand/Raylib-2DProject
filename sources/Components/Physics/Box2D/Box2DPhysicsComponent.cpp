#include "Box2DPhysicsComponent.h"

#include "../../../Physics/Box2D/Box2DWorldManager.h"
#include <iostream>
#include "../../../Helpers/Globals/Globals.h"

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Shape* Shape, 
	const float& Density, const float& Friction, const float& GravityScale, 
	const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: PhysicsComponent(InOwner, InLocation, InRotation, InScale)
{
	Vector3 WorldLocation = GetWorldLocation();
	BodyDef = new b2BodyDef();
	BodyDef->type = Type;
	BodyDef->position = b2Vec2(WorldLocation.x, WorldLocation.y);
	BodyDef->gravityScale = GravityScale;
	Body = ((Box2DWorldManager*)Box2DWorldManager::Get(BOX2D).get())->CreateBody(BodyDef);
	BodyShape = Shape;
	FixtureDef = new b2FixtureDef();
	FixtureDef->shape = BodyShape;
	FixtureDef->density = Density;
	FixtureDef->friction = Friction;
	Fixture = Body->CreateFixture(FixtureDef);

	BindEvents(InOwner);
}

Vector2 Box2DPhysicsComponent::GetWorldPhysicsLocation() const
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
		Vector3 VPosition({ Position.x * PTM_RATIO, Position.y * PTM_RATIO });
		Vector3 WorldPosition = Vector3Add(VPosition, GetComponentLocation());
		GetOwner()->SetActorLocation(WorldPosition, false);
	}
}

void Box2DPhysicsComponent::BindEvents(std::shared_ptr<Actor> InOwner)
{
	InOwner->BindOnLocationSet<Box2DPhysicsComponent, &Box2DPhysicsComponent::OnOwnerLocationSet>(this);
	InOwner->BindOnRotationSet<Box2DPhysicsComponent, &Box2DPhysicsComponent::OnOwnerRotationSet>(this);
}

void Box2DPhysicsComponent::OnOwnerLocationSet(const Vector3& NewLocation)
{
	Vector3 RelativeLocation = GetComponentLocation();
	Body->SetTransform({ (NewLocation.x + RelativeLocation.x) / PTM_RATIO, (NewLocation.y + RelativeLocation.y) / PTM_RATIO }, Body->GetAngle());
}

void Box2DPhysicsComponent::OnOwnerRotationSet(const Quaternion& NewRotation)
{
	float Angle = (NewRotation.y + GetComponentRotation().y) * 3.14 / 180;
	Body->SetTransform(Body->GetPosition(), Angle);
}
