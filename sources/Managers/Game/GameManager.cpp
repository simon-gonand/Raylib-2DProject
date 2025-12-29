#include "GameManager.h"

std::shared_ptr<GameManager> GameManager::Instance = nullptr;

GameManager::GameManager()
{
}

std::shared_ptr<GameManager> GameManager::Get()
{
	if (!Instance)
		Instance.reset(new GameManager());

	return Instance;
}

GameManager::~GameManager()
{
}

std::shared_ptr<World> GameManager::GetWorld()
{
	std::shared_ptr<GameManager> GM = GameManager::Get();
	return GM ? GM->GetWorld() : nullptr;
}

void GameManager::SetWorld(std::shared_ptr<World> NewWorld)
{
	std::shared_ptr<GameManager> GM = GameManager::Get();
	if (GM)
		GM->CurrentWorldInstance = NewWorld;
}
