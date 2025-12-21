#pragma once

#include "../Actors/BaseClass/Actor.h"
#include "../Physics/PhysicsWorldManager.h"

#include <vector>

class World
{
public:
	World();

	void AddActor(std::shared_ptr<Actor> InActor);
	void RemoveActor(std::shared_ptr<Actor> InActor);

	void Update(float DeltaTime);

	void SetCenterMouseEveryFrame(bool bNewValue);

private:
	std::vector<std::shared_ptr<Actor>> Actors;

	std::shared_ptr<PhysicsWorldManager> PhysicsManager;

	bool bCenterMouseEveryFrame = true;
};