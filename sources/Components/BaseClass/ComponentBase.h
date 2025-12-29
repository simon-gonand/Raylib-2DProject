#pragma once

#include <memory>

#include "../../Actors/BaseClass/Actor.h"

class ComponentBase
{
private:
	std::shared_ptr<Actor> Owner;

	bool bIsActive;
	bool bDrawDebug = false;

public:
	ComponentBase(std::shared_ptr<Actor> InOwner, bool bAutoActivate = true);
	virtual ~ComponentBase(){}

	std::shared_ptr<Actor> GetOwner() const;
	void SetOwner(std::shared_ptr<Actor> NewOwner);

	virtual void Initialize() {}
	virtual void Update(float DeltaTime);
	virtual void DrawDebug(float DeltaTime) {}

	virtual void SetDebugUI(std::shared_ptr<class UserWidget> DebugUI);

	void Activate();
	void Deactivate();
	bool IsActive() const;

	Vector3 GetOwnerLocation() const;
	Quaternion GetOwnerRotation() const;
	Vector3 GetOwnerScale() const;

	void SetDrawDebug(bool bInDrawDebug);
};

