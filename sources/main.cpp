#include <raylib.h>

#include <memory>
#include <vector>

#include "Actors/BaseClass/Actor.h"
#include "Actors/Player/Player.h"
#include "Components/Inputs/InputComponent.h"

int main(void) 
{
	const int ScreenWidth = 800;
	const int ScreenHeight = 450;

	InitWindow(ScreenWidth, ScreenHeight, "My First Screen");

	std::vector<std::shared_ptr<Actor>> Actors; // Will be managed by a Level class

	std::shared_ptr<Player> P = std::make_shared<Player>();
	Actors.push_back(P);

	// Target FPS
	SetTargetFPS(60);

	// Main Game Loop
	while (!WindowShouldClose()) 
	{
		float DeltaTime = GetFrameTime();
		
		BeginDrawing();
			ClearBackground(BLACK);
			for (std::shared_ptr<Actor> CurrentActor : Actors)
			{
				CurrentActor->Update(DeltaTime);
				CurrentActor->Draw(); // Might be manage by a renderer component ?
			}
		EndDrawing();
	}

	// De-Init your window
	CloseWindow();

	return 0;
}
