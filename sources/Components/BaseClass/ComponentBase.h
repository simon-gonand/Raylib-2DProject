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

	virtual void Update(float Tick) = 0;
};

