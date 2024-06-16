#pragma once

#include <box2d/box2d.h>

#include "../PhysicsComponent.h"

class Box2DPhysicsComponent : public PhysicsComponent
{
public:
	Box2DPhysicsComponent(std::shared_ptr<Actor> InOwner, b2BodyType Type, b2Shape* Shape, b2Vec2 Position = b2Vec2_zero, float Density = 1.0f, float Friction = 0.3f);
	virtual Vector2 GetWorldLocation() const override;

protected:
	virtual void Update(float Tick) override;

private:
	b2BodyDef* BodyDef;
	b2Body* Body;
	b2Shape* BodyShape;
	b2FixtureDef* FixtureDef;
	b2Fixture* Fixture;

	void BindEvents(std::shared_ptr<Actor> InOwner);

	void OnOwnerLocationSet(const Vector3& NewLocation);
};

