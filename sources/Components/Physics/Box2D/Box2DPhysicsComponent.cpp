#include "Box2DPhysicsComponent.h"

#include "../../../Physics/Box2D/Box2DWorldManager.h"
#include "../../../Helpers/Globals/Globals.h"

#include <iostream>

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Shape* Shape, 
	const float& Density, const float& Friction, const float& GravityScale, bool bFixedRotation, bool bAutoActivate,
	const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: PhysicsComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale)
{
	Vector3 WorldLocation = GetWorldLocation();
	b2BodyDef* BodyDef = new b2BodyDef();
	BodyDef->type = Type;
	BodyDef->position = b2Vec2(WorldLocation.x, WorldLocation.y);
	BodyDef->gravityScale = GravityScale;
	BodyDef->fixedRotation = bFixedRotation;
	Body = ((Box2DWorldManager*)Box2DWorldManager::Get().get())->CreateBody(BodyDef);
	Body->GetUserData().pointer = reinterpret_cast<uintptr_t>(InOwner.get());
	b2FixtureDef* FixtureDef = new b2FixtureDef();
	FixtureDef->shape = Shape;
	FixtureDef->density = Density;
	FixtureDef->friction = Friction;
	Fixture = Body->CreateFixture(FixtureDef);

	BindEvents(InOwner);
}

Vector3 Box2DPhysicsComponent::GetWorldPhysicsLocation() const
{
	b2Vec2 Position = Body->GetPosition();
	return { Position.x, Position.y };
}

Vector3 Box2DPhysicsComponent::GetLinearVelocity() const
{
	b2Vec2 Velocity = Body->GetLinearVelocity();
	return {Velocity.x, Velocity.y };
}

void Box2DPhysicsComponent::SetLinearVelocity(const Vector3& NewVelocity)
{
	Body->SetLinearVelocity({ NewVelocity.x, NewVelocity.y });
}

void Box2DPhysicsComponent::AddLinearVelocity(const Vector3& VelocityToAdd)
{
	b2Vec2 CurrentVelocity = Body->GetLinearVelocity();
	Body->SetLinearVelocity({ CurrentVelocity.x + VelocityToAdd.x, CurrentVelocity.y + VelocityToAdd.y });
}

void Box2DPhysicsComponent::ApplyForce(const Vector3& Force)
{
	Body->ApplyForceToCenter({Force.x, Force.y}, true);
}

void Box2DPhysicsComponent::SetFriction(float NewFriction)
{
	Fixture->SetFriction(NewFriction);
}

float Box2DPhysicsComponent::GetFriction() const
{
	return Fixture->GetFriction();
}

void Box2DPhysicsComponent::SetLinearDamping(float NewAngularDamping)
{
	Body->SetLinearDamping(NewAngularDamping);
}

float Box2DPhysicsComponent::GetLinearDamping() const
{
	return Body->GetLinearDamping();
}

void Box2DPhysicsComponent::EditCollisionShape(b2Shape* NewShape)
{
	if (!NewShape || NewShape == Fixture->GetShape())
		return;

	b2FixtureDef* FixtureDef = new b2FixtureDef();
	FixtureDef->shape = NewShape;
	FixtureDef->density = Fixture->GetDensity();
	FixtureDef->friction = Fixture->GetFriction();
	Body->DestroyFixture(Fixture);
	Fixture = Body->CreateFixture(FixtureDef);
}

b2Body* Box2DPhysicsComponent::GetBody() const
{
	return Body;
}

void Box2DPhysicsComponent::Update(float DeltaTime)
{
	PhysicsComponent::Update(DeltaTime);

	if (GetOwner() && Body->GetType() != b2_staticBody)
	{
		b2Vec2 Position = Body->GetPosition();
		Vector3 VPosition({ Position.x * PTM_RATIO, Position.y * PTM_RATIO });
		Vector3 ComponentLocation = GetComponentLocation();
		Vector3 WorldPosition = Vector3Subtract(VPosition, ComponentLocation);
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
