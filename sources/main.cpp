#include <raylib.h>

#include <memory>
#include <vector>

#include <box2d/box2d.h>

#include "Actors/BaseClass/Actor.h"
#include "Actors/Player/Player.h"
#include "Components/Inputs/InputComponent.h"
#include "Physics/PhysicsWorldManager.h"
#include "Managers/Camera/CameraManager.h"
#include "Managers/Game/GameManager.h"
#include "Helpers/Globals/Globals.h"
#include "Actors/TileMap/TileMap.h"
#include "World/World.h"
#include "UI/UserWidgets/Custom/TextsWithBackground/TextsWithBackgroundUserWidget.h"

// Disable the console in Windows releases (from https://keasigmadelta.com/blog/raylib-hide-the-console-window-on-windows-release-builds/?srsltid=AfmBOoo2k-zfGUYh_a4LCI9-RXJwu760A66KR_1X9CEwQs8MmJBmA7dK)
# if defined(WIN32) && !defined(_DEBUG)
# pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
# endif


int main(void) 
{
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

	InitWindow(ScreenWidth, ScreenHeight, "2D Project");

	std::shared_ptr<World> W = std::make_shared<World>();
	GameManager::SetWorld(W);

	Vector2 TileSize = { 16.0f, 16.0f };
	std::shared_ptr<TileMap> TM = std::make_shared<TileMap>("assets/TileMap/TMX/TestGround.tmx");
	W->AddActor(TM);
	TM->Initialize();
	TM->SetActorLocation({ -30 * 16.0f / 2, -20 * 16.0f / 2, 0.0f, });
	TM->SetActorScale({ 0.05f, 0.05f });

	std::shared_ptr<Player> P = std::make_shared<Player>();
	W->AddActor(P);
	P->Initialize();

	// Target FPS
	SetTargetFPS(60);

	// Main Game Loop
	while (!WindowShouldClose()) 
	{
		float DeltaTime = GetFrameTime();
		
		BeginDrawing();
			ClearBackground(BLACK);

			Camera2D Camera = CameraManager::Get()->GetCameraToUse();
			BeginMode2D(Camera);
				W->Update(DeltaTime);
			EndMode2D();

			W->UpdateUI(DeltaTime);
		EndDrawing();
	}

	// De-Init your window
	CloseWindow();

	return 0;
}
