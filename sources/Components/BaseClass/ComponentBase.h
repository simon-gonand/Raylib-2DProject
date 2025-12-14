#pragma once

#include <memory>

#include "../../Actors/BaseClass/Actor.h"

class ComponentBase
{
private:
	std::shared_ptr<Actor> Owner;

public:
	ComponentBase(std::shared_ptr<Actor> InOwner);
	virtual ~ComponentBase(){}

	std::shared_ptr<Actor> GetOwner() const;
	void SetOwner(std::shared_ptr<Actor> NewOwner);

	virtual void Initialize() {};
	virtual void Update(float DeltaTime) = 0;

	Vector3 GetOwnerLocation() const;
	Quaternion GetOwnerRotation() const;
	Vector3 GetOwnerScale() const;
};

