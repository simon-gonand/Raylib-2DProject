#pragma once

#include "../Actors/BaseClass/Actor.h"
#include "../Physics/PhysicsWorldManager.h"

#include <vector>
#include "../UI/UserWidgets/BaseClass/UserWidget.h"
#include "../Actors/Player/Player.h"

class World
{
public:
	World();

	void AddActor(std::shared_ptr<Actor> InActor);
	void RemoveActor(std::shared_ptr<Actor> InActor);

	std::shared_ptr<Player> GetPlayer() const;

	void AddUserWidget(std::shared_ptr<UserWidget> InUserWidget);
	void RemoveUserWidget(std::shared_ptr<UserWidget> InUserWidget);

	void Update(float DeltaTime);
	void UpdateUI(float DeltaTime);

	void SetCenterMouseEveryFrame(bool bNewValue);

private:
	std::vector<std::shared_ptr<Actor>> Actors;
	std::vector<std::shared_ptr<UserWidget>> UserWidgets;

	std::shared_ptr<Player> PlayerActor;

	std::shared_ptr<PhysicsWorldManager> PhysicsManager;

	bool bCenterMouseEveryFrame = false;
};