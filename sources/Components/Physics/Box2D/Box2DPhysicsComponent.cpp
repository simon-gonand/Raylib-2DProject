#include "Box2DPhysicsComponent.h"

#include "../../../Physics/Box2D/Box2DWorldManager.h"
#include "../../../Helpers/Globals/Globals.h"

#include <iostream>

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Polygon Shape,
	const float& Density, const float& Friction, const float& GravityScale, bool bFixedRotation, bool bAutoActivate,
	const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: PhysicsComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale)
{
	CreateBody(Type, GravityScale, bFixedRotation, InOwner);

	b2ShapeDef ShapeDef = CreateShapeDef(Density, Friction);
	ShapeId = b2CreatePolygonShape(Body, &ShapeDef, &Shape);

	BindEvents(InOwner);
}

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Capsule Shape, 
	const float& Density, const float& Friction, const float& GravityScale, bool bFixedRotation, bool bAutoActivate, 
	const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: PhysicsComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale)
{
	CreateBody(Type, GravityScale, bFixedRotation, InOwner);

	b2ShapeDef ShapeDef = CreateShapeDef(Density, Friction);
	ShapeId = b2CreateCapsuleShape(Body, &ShapeDef, &Shape);

	BindEvents(InOwner);
}

Box2DPhysicsComponent::Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Circle Shape, 
	const float& Density, const float& Friction, const float& GravityScale, bool bFixedRotation, bool bAutoActivate, 
	const Vector3& InLocation, const Quaternion& InRotation, const Vector3& InScale)
	: PhysicsComponent(InOwner, bAutoActivate, InLocation, InRotation, InScale)
{
	CreateBody(Type, GravityScale, bFixedRotation, InOwner);

	b2ShapeDef ShapeDef = CreateShapeDef(Density, Friction);
	ShapeId = b2CreateCircleShape(Body, &ShapeDef, &Shape);

	BindEvents(InOwner);
}

Vector3 Box2DPhysicsComponent::GetWorldPhysicsLocation() const
{
	b2Vec2 Position = b2Body_GetPosition(Body);
	return { Position.x, Position.y };
}

Vector3 Box2DPhysicsComponent::GetLinearVelocity() const
{
	b2Vec2 Velocity = b2Body_GetLinearVelocity(Body);
	return {Velocity.x, Velocity.y };
}

void Box2DPhysicsComponent::SetLinearVelocity(const Vector3& NewVelocity)
{
	b2Body_SetLinearVelocity(Body, { NewVelocity.x, NewVelocity.y });
}

void Box2DPhysicsComponent::AddLinearVelocity(const Vector3& VelocityToAdd)
{
	b2Vec2 CurrentVelocity = b2Body_GetLinearVelocity(Body);
	b2Body_SetLinearVelocity(Body, { CurrentVelocity.x + VelocityToAdd.x, CurrentVelocity.y + VelocityToAdd.y });
}

void Box2DPhysicsComponent::ApplyForce(const Vector3& Force)
{
	b2Body_ApplyForceToCenter(Body, { Force.x, Force.y }, true);
}

void Box2DPhysicsComponent::SetFriction(float NewFriction)
{
	b2Shape_SetFriction(ShapeId, NewFriction);
}

float Box2DPhysicsComponent::GetFriction() const
{
	return b2Shape_GetFriction(ShapeId);
}

void Box2DPhysicsComponent::SetLinearDamping(float NewLinearDamping)
{
	b2Body_SetLinearDamping(Body, NewLinearDamping);
}

float Box2DPhysicsComponent::GetLinearDamping() const
{
	return b2Body_GetLinearDamping(Body);
}

void Box2DPhysicsComponent::EditCollisionShape(b2Polygon NewShape)
{
	b2ShapeDef ShapeDef = CreateShapeDef(b2Shape_GetDensity(ShapeId), b2Shape_GetFriction(ShapeId));

	b2DestroyShape(ShapeId, false);

	ShapeId = b2CreatePolygonShape(Body, &ShapeDef, &NewShape);
}

void Box2DPhysicsComponent::EditCollisionShape(b2Capsule NewShape)
{
	b2ShapeDef ShapeDef = CreateShapeDef(b2Shape_GetDensity(ShapeId), b2Shape_GetFriction(ShapeId));

	b2DestroyShape(ShapeId, false);

	ShapeId = b2CreateCapsuleShape(Body, &ShapeDef, &NewShape);
}

void Box2DPhysicsComponent::EditCollisionShape(b2Circle NewShape)
{
	b2ShapeDef ShapeDef = CreateShapeDef(b2Shape_GetDensity(ShapeId), b2Shape_GetFriction(ShapeId));

	b2DestroyShape(ShapeId, false);

	ShapeId = b2CreateCircleShape(Body, &ShapeDef, &NewShape);
}

const b2BodyId& Box2DPhysicsComponent::GetBody() const
{
	return Body;
}

void Box2DPhysicsComponent::Update(float DeltaTime)
{
	PhysicsComponent::Update(DeltaTime);

	if (GetOwner() && b2Body_GetType(Body) != b2_staticBody)
	{
		b2Vec2 Position = b2Body_GetPosition(Body);
		Vector3 VPosition({ Position.x * PTM_RATIO, Position.y * PTM_RATIO });
		Vector3 ComponentLocation = GetComponentLocation();
		Vector3 WorldPosition = Vector3Subtract(VPosition, ComponentLocation);
		GetOwner()->SetActorLocation(WorldPosition, false);
	}
}

void Box2DPhysicsComponent::CreateBody(const b2BodyType& Type, float GravityScale, bool bFixedRotation, std::shared_ptr<Actor> InOwner)
{
	Vector3 WorldLocation = GetWorldLocation();

	b2BodyDef BodyDef = b2DefaultBodyDef();
	BodyDef.type = Type;
	BodyDef.position = b2Vec2({ WorldLocation.x / PTM_RATIO, WorldLocation.y / PTM_RATIO });
	BodyDef.gravityScale = GravityScale;
	BodyDef.fixedRotation = bFixedRotation;
	Body = ((Box2DWorldManager*)Box2DWorldManager::Get().get())->CreateBody(&BodyDef, InOwner.get());
}

b2ShapeDef Box2DPhysicsComponent::CreateShapeDef(float Density, float Friction)
{
	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = Density;
	ShapeDef.material.friction = Friction;

	return ShapeDef;
}

void Box2DPhysicsComponent::BindEvents(std::shared_ptr<Actor> InOwner)
{
	InOwner->BindOnLocationSet<Box2DPhysicsComponent, &Box2DPhysicsComponent::OnOwnerLocationSet>(this);
	InOwner->BindOnRotationSet<Box2DPhysicsComponent, &Box2DPhysicsComponent::OnOwnerRotationSet>(this);
}

void Box2DPhysicsComponent::OnOwnerLocationSet(const Vector3& NewLocation)
{
	Vector3 RelativeLocation = GetComponentLocation();
	b2Body_SetTransform(Body, { (NewLocation.x + RelativeLocation.x) / PTM_RATIO, (NewLocation.y + RelativeLocation.y) / PTM_RATIO }, b2Body_GetRotation(Body));
}

void Box2DPhysicsComponent::OnOwnerRotationSet(const Quaternion& NewRotation)
{
	float Angle = (NewRotation.y + GetComponentRotation().y) * 3.14 / 180;
	b2Body_SetTransform(Body, b2Body_GetPosition(Body), b2MakeRot(Angle));
}
