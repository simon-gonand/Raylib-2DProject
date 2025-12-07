#include <raylib.h>

#include <memory>
#include <vector>

#include <box2d/box2d.h>

#include "Actors/BaseClass/Actor.h"
#include "Actors/Player/Player.h"
#include "Components/Inputs/InputComponent.h"
#include "Physics/PhysicsWorldManager.h"
#include "Managers/Camera/CameraManager.h"
#include "Helpers/Globals/Globals.h"
#include "Actors/TileMap/TileMap.h"

int main(void) 
{
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

	InitWindow(ScreenWidth, ScreenHeight, "2D Project");

	std::vector<std::shared_ptr<Actor>> Actors; // Will be managed by a Level class

	std::shared_ptr<PhysicsWorldManager> WorldManager = std::shared_ptr<PhysicsWorldManager>(PhysicsWorldManager::Get(BOX2D));
	if(WorldManager)
	{
		WorldManager->Initialize({ 0.0f, 9.81f, 0.0f});
		WorldManager->SetDebugMode(true);
	}

	Vector2 TileSize = { 16.0f, 16.0f };
	std::shared_ptr<TileMap> TM2 = std::make_shared<TileMap>("assets/TileMap/TMX/TestGround.tmx");
	TM2->Initialize();
	TM2->SetActorScale({ 0.05f, 0.05f });
	TM2->SetActorLocation({ -30 * 16.0f / 2, -20 * 16.0f / 2, 2.0f });
	Actors.push_back(TM2);

	std::shared_ptr<Player> P = std::make_shared<Player>();
	P->Initialize();
	Actors.push_back(P);

	// Target FPS
	SetTargetFPS(60);

	// Main Game Loop
	while (!WindowShouldClose()) 
	{
		float DeltaTime = GetFrameTime();
		
		// Physics Update
		WorldManager->Update(DeltaTime);

		BeginDrawing();
			ClearBackground(BLACK);
			Camera2D Camera = CameraManager::Get()->GetCameraToUse();
			BeginMode2D(Camera);
				for (std::shared_ptr<Actor> CurrentActor : Actors)
				{
					CurrentActor->Update(DeltaTime);
					CurrentActor->PostUpdate();
				}
				WorldManager->DrawDebug();
			EndMode2D();
		EndDrawing();
	}

	// De-Init your window
	CloseWindow();

	return 0;
}
