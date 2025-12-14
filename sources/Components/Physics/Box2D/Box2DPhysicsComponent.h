#pragma once

#include <box2d/box2d.h>

#include "../PhysicsComponent.h"

class Box2DPhysicsComponent : public PhysicsComponent
{
public:
	Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Shape* Shape, 
		const float& Density = 1.0f, const float& Friction = 0.3f, const float& GravityScale = 1.0f, bool bFixedRotation = false,
		const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f });
	
	virtual Vector3 GetWorldPhysicsLocation() const override;
	virtual Vector3 GetLinearVelocity() const override;

	virtual void SetLinearVelocity(const Vector3& NewVelocity) override;
	virtual void AddLinearVelocity(const Vector3& VelocityToAdd) override;

protected:
	virtual void Update(float DeltaTime) override;

private:
	b2BodyDef* BodyDef;
	b2Body* Body;
	b2Shape* BodyShape;
	b2FixtureDef* FixtureDef;
	b2Fixture* Fixture;

	void BindEvents(std::shared_ptr<Actor> InOwner);

	void OnOwnerLocationSet(const Vector3& NewLocation);
	void OnOwnerRotationSet(const Quaternion& NewRotation);
};

