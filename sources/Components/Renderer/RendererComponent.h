#pragma once

#include "../BaseClass/ComponentBase.h"

class RendererComponent : public ComponentBase 
{
protected:
	RendererComponent(std::shared_ptr<Actor> Owner);

	Vector3 GetOwnerLocation() const;
	Quaternion GetOwnerRotation() const;
	Vector3 GetOwnerScale() const;
};