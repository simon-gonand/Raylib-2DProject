#pragma once

#include <list>
#include <memory>
#include "raylib.h"

class Actor: public std::enable_shared_from_this<Actor>
{
private:
	std::list<std::shared_ptr<class ComponentBase>> Components;

	Transform ActorTransform; // Will be stored in a Root Component ?
	
public:
	Actor();
	virtual ~Actor(){}

	void AddComponent(std::shared_ptr<ComponentBase> Component);
	void RemoveComponent(std::shared_ptr<ComponentBase> Component);
	const std::list<std::shared_ptr<ComponentBase>>& GetAllComponents() const;

	const Transform& GetActorTransform() const;
	const Vector3& GetActorLocation() const;
	const Quaternion& GetActorRotation() const;
	const Vector3& GetActorScale() const;

	void SetActorLocation(const Vector3& NewLocation);
	void AddActorLocation(const Vector3& AddedLocation);
	void SetActorRotation(const Quaternion& NewRotation);
	void SetActorScale(const Vector3& NewScale);

	virtual void Update(float Tick);
	virtual void Draw() = 0;
};

