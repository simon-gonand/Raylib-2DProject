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

	HideCursor();
}

void World::AddActor(std::shared_ptr<Actor> InActor)
{
	Actors.push_back(InActor);
}

void World::RemoveActor(std::shared_ptr<Actor> InActor)
{
	std::vector<std::shared_ptr<Actor>>::iterator ActorToRemove = std::find(Actors.begin(), Actors.end(), InActor);
	if (ActorToRemove == Actors.end())
		return;

	Actors.erase(ActorToRemove);
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

void World::SetCenterMouseEveryFrame(bool bNewValue)
{
	bCenterMouseEveryFrame = bNewValue;
}
