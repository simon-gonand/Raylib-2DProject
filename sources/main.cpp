#include <raylib.h>

#include <memory>
#include <vector>

#include <box2d/box2d.h>

#include "Actors/BaseClass/Actor.h"
#include "Actors/Player/Player.h"
#include "Components/Inputs/InputComponent.h"
#include "Physics/PhysicsWorldManager.h"
#include "Actors/Statics/Ground.h"
#include "Managers/Camera/CameraManager.h"


int main(void) 
{
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

	InitWindow(ScreenWidth, ScreenHeight, "2D Project");

	std::vector<std::shared_ptr<Actor>> Actors; // Will be managed by a Level class

	std::shared_ptr<PhysicsWorldManager> WorldManager = std::shared_ptr<PhysicsWorldManager>(PhysicsWorldManager::Get(BOX2D));
	if(WorldManager)
	{
		WorldManager->Initialize({ 0.0f, -9.81f, 0.0f});
	}

	// TODO Player and Ground don't want to collide well, try to find why Player is going so far. Maybe be rendering the debug of the b2Shape

	std::shared_ptr<Ground> G = std::make_shared<Ground>();
	G->Initialize();
	Actors.push_back(G);

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
					CurrentActor->Draw({ (float)GetScreenWidth(), (float)GetScreenHeight() }); // Might be manage by a renderer component ?
				}
			EndMode2D();
		EndDrawing();
	}

	// De-Init your window
	CloseWindow();

	return 0;
}
