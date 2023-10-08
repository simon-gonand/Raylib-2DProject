#pragma once

#include <list>
#include <memory>
#include "../../Helpers/Math/Transforms/Transform2D.h"

class Actor: public std::enable_shared_from_this<Actor>
{
private:
	std::list<std::shared_ptr<class ComponentBase>> Components;

	Transform2D* Transform; // Will be stored in a Root Component ?
	
public:
	Actor();
	virtual ~Actor(){}

	void AddComponent(std::shared_ptr<ComponentBase> Component);
	void RemoveComponent(std::shared_ptr<ComponentBase> Component);
	const std::list<std::shared_ptr<ComponentBase>>& GetAllComponents() const;

	Transform2D* GetActorTransform() const;
	const MyVector2& GetActorLocation() const;
	const float& GetActorRotation() const;
	const MyVector2& GetActorScale() const;

	void SetActorLocation(const MyVector2& NewLocation);
	void AddActorLocation(const MyVector2& AddedLocation);
	void SetActorRotation(const float& NewRotation);
	void SetActorScale(const MyVector2& NewScale);

	virtual void Update(float Tick);
	virtual void Draw() = 0;
};

