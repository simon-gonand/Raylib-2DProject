#pragma once

#include"../BaseClass/TransformComponent.h"

#include <vector>

class PhysicsComponent: public TransformComponent
{
public:
	virtual Vector3 GetWorldPhysicsLocation() const = 0;
	virtual Vector3 GetLinearVelocity() const = 0;

	virtual void SetLinearVelocity(const Vector3& NewVelocity) = 0;
	virtual void AddLinearVelocity(const Vector3& NewVelocity) = 0;

	virtual void ApplyForce(const Vector3& Force) = 0;

	virtual void SetFriction(float NewFriction) = 0;
	virtual float GetFriction() const = 0;

	virtual void SetLinearDamping(float NewLinearDamping) = 0;
	virtual float GetLinearDamping() const = 0;

	template<class C, void (C::* Function)(PhysicsComponent*)>
	void BindOnBeginOverlap(C* Instance)
	{
		DelegateBase<void, PhysicsComponent*>* OnBeginOverlapDelegate = new DelegateBase<void, PhysicsComponent*>();
		OnBeginOverlapDelegate->Bind<C, Function>(Instance);
		OnBeginOverlap.push_back(OnBeginOverlapDelegate);
	}

	template<class C, void (C::* Function)(PhysicsComponent*)>
	void BindOnEndOverlap(C* Instance)
	{
		DelegateBase<void, PhysicsComponent*>* OnEndOverlapDelegate = new DelegateBase<void, PhysicsComponent*>();
		OnEndOverlapDelegate->Bind<C, Function>(Instance);
		OnEndOverlap.push_back(OnEndOverlapDelegate);
	}

protected:
	PhysicsComponent(std::shared_ptr<Actor> InOwner, bool bAutoActivate = true, const Vector3& InLocation = { 0.0f }, const Quaternion& InRotation = { 0.0f }, const Vector3& InScale = { 1.0f, 1.0f, 1.0f });

	void BroadcastOnBeginOverlap(PhysicsComponent* InVisitor) const;
	void BroadcastOnEndOverlap(PhysicsComponent* InVisitor) const;

	std::vector<DelegateBase<void, PhysicsComponent*>*> OnBeginOverlap;
	std::vector<DelegateBase<void, PhysicsComponent*>*> OnEndOverlap;
};

