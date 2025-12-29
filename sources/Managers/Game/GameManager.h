#pragma once

#include<memory>
#include "../../World/World.h"

class GameManager
{
private:
	static std::shared_ptr<GameManager> Instance;

	std::shared_ptr<World> CurrentWorldInstance;

	GameManager();

public:
	static std::shared_ptr<GameManager> Get();

	~GameManager();

	GameManager(GameManager& InInputManager) = delete;
	void operator=(const GameManager& InInputManager) = delete;

	static std::shared_ptr<World> GetWorld();
	static void SetWorld(std::shared_ptr<World> NewWorld);
};

