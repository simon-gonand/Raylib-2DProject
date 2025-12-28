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
#include "World/World.h"
#include "UI/UserWidgets/Custom/TextsWithBackground/TextsWithBackgroundUserWidget.h"

int main(void) 
{
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

	InitWindow(ScreenWidth, ScreenHeight, "2D Project");

	World* W = new World();

	Vector2 TileSize = { 16.0f, 16.0f };
	std::shared_ptr<TileMap> TM = std::make_shared<TileMap>("assets/TileMap/TMX/TestGround.tmx");
	TM->Initialize();
	TM->SetActorScale({ 0.05f, 0.05f });
	TM->SetActorLocation({ -30 * 16.0f / 2, -20 * 16.0f / 2, 2.0f });
	W->AddActor(TM);

	std::shared_ptr<Player> P = std::make_shared<Player>();
	P->Initialize();
	W->AddActor(P);

	std::shared_ptr<TextsWithBackgroundUserWidget> TXBUW = std::make_shared<TextsWithBackgroundUserWidget>(
		"", "Pretty long Text Test to see auto size", true, 
		Vector2{0.0f}, 0.0f, Vector2{1.0f, 1.0f}, 1.0f, Vector4{10.0f, 10.0f, 10.0f, 10.0f});
	TXBUW->Initialize();
	W->AddUserWidget(TXBUW);

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
