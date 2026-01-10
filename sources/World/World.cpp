#include "World.h"

World::World()
{
	PhysicsWorldManager::SetPhysicsEngineType(BOX2D);
	PhysicsManager = std::shared_ptr<PhysicsWorldManager>(PhysicsWorldManager::Get());
	if (PhysicsManager)
	{
		PhysicsManager->Initialize({ 0.0f, 9.81f, 0.0f });
		PhysicsManager->SetDebugMode(true);
	}

	SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
	DisableCursor();
}

void World::AddActor(std::shared_ptr<Actor> InActor)
{
	if (!InActor)
		return;

	Actors.push_back(InActor);

	if (std::shared_ptr<Player> InPlayer = std::dynamic_pointer_cast<Player>(InActor))
		PlayerActor = InPlayer;
}

void World::RemoveActor(std::shared_ptr<Actor> InActor)
{
	std::vector<std::shared_ptr<Actor>>::iterator ActorToRemove = std::find(Actors.begin(), Actors.end(), InActor);
	if (ActorToRemove == Actors.end())
		return;

	Actors.erase(ActorToRemove);
}

std::shared_ptr<Player> World::GetPlayer() const
{
	return PlayerActor;
}

void World::AddUserWidget(std::shared_ptr<UserWidget> InUserWidget)
{
	if (!InUserWidget)
		return;

	UserWidgets.push_back(InUserWidget);
}

void World::RemoveUserWidget(std::shared_ptr<UserWidget> InUserWidget)
{
	std::vector<std::shared_ptr<UserWidget>>::iterator UserWidgetToRemove = std::find(UserWidgets.begin(), UserWidgets.end(), InUserWidget);
	if (UserWidgetToRemove == UserWidgets.end())
		return;

	UserWidgets.erase(UserWidgetToRemove);
}

void World::Update(float DeltaTime)
{
	if(PhysicsManager)
		PhysicsManager->Update(DeltaTime);

	for (std::shared_ptr<Actor> CurrentActor : Actors)
	{
		CurrentActor->Update(DeltaTime);
		CurrentActor->PostUpdate();
	}

	if (PhysicsManager)
		PhysicsManager->DrawDebug();

	if (bCenterMouseEveryFrame)
		SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
}

void World::UpdateUI(float DeltaTime)
{
	for (std::shared_ptr<UserWidget> UI : UserWidgets)
	{
		if (UI)
			UI->Update(DeltaTime);
	}
}

void World::SetCenterMouseEveryFrame(bool bNewValue)
{
	bCenterMouseEveryFrame = bNewValue;
}
