#include "Player.h"

#include <memory>
#include <iostream>
#include <functional>
#include <raylib.h>
#include "raymath.h"

#include "../../Components/Inputs/InputComponent.h"
#include "../BaseClass/Actor.h"
#include "../../Managers/Inputs/InputManager.h"
#include "../../Components/Physics/Box2D/Box2DPhysicsComponent.h"
#include "../../Components/Camera/PlayerCameraComponent.h"
#include "../../Helpers/Math/Vectors/Vectors.h"
#include "../../Helpers/Globals/Globals.h"
#include "../../Components/Renderer/2DRenderer/SpriteSheet2DRenderer/SpriteSheet2DRendererComponent.h"
#include "Animation/PlayerAnimationManager.h"
#include "../../Components/Movements/MovementComponent.h"
#include "../../MovementModes/JumpingMovementMode/JumpingMovementMode.h"
#include "../../MovementModes/FallingMovementMode/FallingMovementMode.h"
#include "../../MovementModes/SlidingMovementMode/SlidingMovementMode.h"
#include "../../MovementModes/GroundMovementMode/GroundMovementMode.h"
#include "../../MovementModes/ThrownMovementMode/ThrownMovementMode.h"
#include "../../MovementModes/ThrownMovementMode/GrapplingThrownMovementMode/GrapplingThrownMovementMode.h"
#include "../../MovementModes/GrapplingBalanceMovementMode/GrapplingBalanceMovementMode.h"
#include "../../Components/Movements/UI/MovementComponentDebugUserWidget.h"

Player::Player()
{
}

Player::~Player() 
{
}

void Player::Initialize()
{
	Actor::Initialize();

	std::shared_ptr<Actor> PlayerSPtr = shared_from_this();

	InputComp = std::make_shared<InputComponent>(PlayerSPtr);
	AddComponent(InputComp);
	InputComp->BindInput<Player, &Player::Jump>("Jump", DOWN, this);
	InputComp->BindInput<Player, &Player::Jump>("Jump", RELEASED, this);
	InputComp->BindInput<Player, &Player::Slide>("Slide", DOWN, this);
	InputComp->BindInput<Player, &Player::Slide>("Slide", RELEASED, this);
	InputComp->BindInput<Player, &Player::AttractHook>("AttractHook", PRESSED, this);
	InputComp->BindInput<Player, &Player::ClearAttractHook>("AttractHook", RELEASED, this);
	InputComp->BindInput<Player, &Player::BalanceHook>("BalanceHook", PRESSED, this);
	InputComp->BindInput<Player, &Player::ClearBalanceHook>("BalanceHook", RELEASED, this);
	InputComp->BindAxis<Player, &Player::Move>("Move", this);
	InputComp->BindAxis<Player, &Player::Aim>("Aim", this);

	ActorInitialPostion = { -150.0f, -50.0f, 0.0f};
	SetActorLocation(ActorInitialPostion);
	SetActorRotation(QuaternionIdentity());
	SetActorScale({ 1.0f, 1.0f });

	b2Polygon GroundPhysicsShape = b2MakeBox(0.8f, 1.6f);
	CollisionShapes.insert({ EMovementMode::GROUND, GroundPhysicsShape });

	b2Polygon SlidingPhysicsShape = b2MakeOffsetBox(1.3f, 0.5f, b2Vec2({ 0.0f, 1.0f }), b2MakeRot(0.0f));
	CollisionShapes.insert({ EMovementMode::SLIDING, SlidingPhysicsShape });

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, GroundPhysicsShape, false, 1.0f, 0.0f, 3.0f, true);
	AddComponent(PhysicsComp);

	CameraComp = std::make_shared<PlayerCameraComponent>(PlayerSPtr, true, Vector2{ ActorInitialPostion.x, ActorInitialPostion.y }, Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 0.0f, 2.5f, Vector2{100.0f, 70.0f}, 15.0f);
	AddComponent(CameraComp);
	//CameraComp->SetDrawDebug(true);

	// Create Animation Manager + add Idle animation
	std::shared_ptr<AnimationManager> AnimManager = CreatePlayerAnimationManager();
	RendererComp = std::make_shared<SpriteSheet2DRendererComponent>(PlayerSPtr, "", true, Vector3({ 2.5f, -15.0f }), QuaternionIdentity(), Vector3({1.0f, 1.0f}), Vector2({3.0f, 3.0f}), AnimManager);
	AddComponent(RendererComp);

	MovementComp = std::make_shared<MovementComponent>(PlayerSPtr, PhysicsComp, true);
	MovementComp->AddNewMovementMode(EMovementMode::GROUND, std::make_shared<GroundMovementMode>(75.0f, 60.0f, 15.0f));
	MovementComp->AddNewMovementMode(EMovementMode::JUMPING, std::make_shared<JumpingMovementMode>(56.0f, 10.0f, 15.0f, -15.0f, 2, MovementComp));
	MovementComp->AddNewMovementMode(EMovementMode::FALLING, std::make_shared<FallingMovementMode>(56.0f, 10.0f, 15.0f, 30.0f, 1.5f));
	MovementComp->AddNewMovementMode(EMovementMode::SLIDING, std::make_shared<SlidingMovementMode>(21.5f, 15.0f, 15.0f, MovementComp, 12.5f, 20.0f, 25.0f));
	MovementComp->AddNewMovementMode(EMovementMode::THROWN, std::make_shared<ThrownMovementMode>(PhysicsComp, MovementComp));
	MovementComp->AddNewMovementMode(EMovementMode::GRAPPLING_THROWN, std::make_shared<GrapplingThrownMovementMode>(PhysicsComp, MovementComp, 75.0f, 20.0f, 20.0f, 0.5f));
	MovementComp->AddNewMovementMode(EMovementMode::GRAPPLING_BALANCE, std::make_shared<GrapplingBalanceMovementMode>(15.0f, 3.0f, 15.0f, PhysicsComp, 0.25f));
	MovementComp->BindToOnMovementModeSwitch<Player, &Player::OnMovementModeSwitch>(this);
	/*MovementComp->SetDrawDebug(true);
	std::shared_ptr<MovementComponentDebugUserWidget> PlayerMovementModeDebugUI = std::make_shared<MovementComponentDebugUserWidget>(MovementComp);
	MovementComp->SetDebugUI(PlayerMovementModeDebugUI);*/
	AddComponent(MovementComp);

	GrapplingHookComp = std::make_shared<GrapplingHookComponent<Renderer2DComponent, CableRendererComponent>>(PlayerSPtr, 
		"assets/Aim/GrapplingHookAim.png", Vector2({1.5f, 1.5f}), 225.0f, 25.0f, 30.0f, 150.0f, 100.0f);
	GrapplingHookComp->SetDrawDebug(false);
	AddComponent(GrapplingHookComp);

	MovementComp->SwitchMovementMode(EMovementMode::FALLING);
}

void Player::Move(const Vector2& Scale)
{
	float Magnitude = Vector2Length(Scale);
	MovementComp->SetMovementInput(Scale);
}

void Player::Aim(const Vector2& Scale)
{
	GrapplingHookComp->UpdateAimPosition(Scale);
}

void Player::Slide(const float& Scale, const InputTrigger& Trigger)
{
	if (Trigger == DOWN)
	{
		MovementComp->SwitchMovementMode(EMovementMode::SLIDING);
	}
	else 
	{
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}

}

void Player::Jump(const float& Scale, const InputTrigger& Trigger)
{
	if (Trigger == DOWN)
	{
		if (MovementComp->GetCurrentMovementMode() != EMovementMode::JUMPING && MovementComp->GetCurrentMovementMode() != EMovementMode::FALLING)
			bCanIncrementJump = true;

		MovementComp->SwitchMovementMode(EMovementMode::JUMPING);
		GrapplingHookComp->ClearBalanceGrapplingHook();
		const std::shared_ptr<MovementModeBase> CurrentMovementModeObj = MovementComp->GetCurrentMovementModeObj();
		if (bCanIncrementJump)
		{
			if (std::shared_ptr<JumpingMovementMode> JumpingMode = std::dynamic_pointer_cast<JumpingMovementMode>(CurrentMovementModeObj))
			{
				if (JumpingMode->IncrementJumpCount() && OnIncrementJumpCount)
				{
					OnIncrementJumpCount->Invoke(JumpingMode->GetJumpCount());
				}
				bCanIncrementJump = false;
			}
		}
	}
	else
	{
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
		bCanIncrementJump = true;
	}
}

void Player::AttractHook(const float& Scale, const InputTrigger& Trigger)
{
 	GrapplingHookComp->TriggerAttractGrapplingHook();
}

void Player::ClearAttractHook(const float& Scale, const InputTrigger& Trigger)
{
	if (GrapplingHookComp->ClearAttractGrapplingHook() && MovementComp)
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
}

void Player::BalanceHook(const float& Scale, const InputTrigger& Trigger)
{
 	GrapplingHookComp->TriggerBalanceGrapplingHook();
}

void Player::ClearBalanceHook(const float& Scale, const InputTrigger& Trigger)
{
	if(GrapplingHookComp->ClearBalanceGrapplingHook() && MovementComp)
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
}

void Player::Update(float DeltaTime)
{
	UpdateCollision();
	Actor::Update(DeltaTime);
}

void Player::PostUpdate()
{
	// Is Player Falling
	Vector3 CurrentVelocity = PhysicsComp->GetLinearVelocity();
	if (FloatEquals(CurrentVelocity.y, 0.0f)) 
	{
		if(GetCurrentMovementMode() != EMovementMode::SLIDING && 
			GetCurrentMovementMode() != EMovementMode::THROWN &&
			GetCurrentMovementMode() != EMovementMode::GRAPPLING_THROWN &&
			GetCurrentMovementMode() != EMovementMode::GRAPPLING_BALANCE )
			MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}
	else if (GetCurrentMovementMode() != EMovementMode::JUMPING && 
		GetCurrentMovementMode() != EMovementMode::SLIDING &&
		GetCurrentMovementMode() != EMovementMode::THROWN && 
		GetCurrentMovementMode() != EMovementMode::GRAPPLING_THROWN &&
		GetCurrentMovementMode() != EMovementMode::GRAPPLING_BALANCE)
	{
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
	}

	// Set Player Orientation
	Vector3 NormalizedVelocity = Vector3Normalize(CurrentVelocity);
	Quaternion RendererComponentRotation = RendererComp->GetComponentRotation();
	if (NormalizedVelocity.x < 0.0f) {
		RendererComponentRotation.y = -180.0f;
	}
	else if (NormalizedVelocity.x > 0.0f) {
		RendererComponentRotation.y = 0.0f;
	}
	RendererComp->SetComponentRotation(RendererComponentRotation);
}

void Player::Respawn()
{
	SetActorLocation(ActorInitialPostion);
}

EMovementMode Player::GetCurrentMovementMode() const
{
	return MovementComp->GetCurrentMovementMode();
}

EMovementMode Player::GetPreviousMovementMode() const
{
	return MovementComp->GetPreviousMovementMode();
}

std::shared_ptr<class PhysicsComponent> Player::GetPhysicsComponent()
{
	return PhysicsComp;
}

std::shared_ptr<AnimationManager> Player::CreatePlayerAnimationManager()
{
	std::shared_ptr<PlayerAnimationManager> Result = std::make_shared<PlayerAnimationManager>();
	Result->Initialize(std::static_pointer_cast<Player>(shared_from_this()));
	return Result;
}

void Player::UpdateCollision()
{
	if (MovementComp->GetCurrentMovementMode() != MovementComp->GetPreviousMovementMode())
	{
		b2Polygon Shape;
		auto CollisionShape = CollisionShapes.find(MovementComp->GetCurrentMovementMode());
		if (CollisionShape != CollisionShapes.end())
		{
			if (MovementComp->GetCurrentMovementMode() == CurrentMovementModeShape)
				return;
			Shape = CollisionShape->second;
			CurrentMovementModeShape = MovementComp->GetCurrentMovementMode();
		}
		else
		{
			if (CurrentMovementModeShape == EMovementMode::GROUND)
				return;
				
			Shape = CollisionShapes[EMovementMode::GROUND];
			CurrentMovementModeShape = EMovementMode::GROUND;
		}
		std::shared_ptr<Box2DPhysicsComponent> Box2DPhysicsComp = std::dynamic_pointer_cast<Box2DPhysicsComponent>(PhysicsComp);
		if (Box2DPhysicsComp)
		{
			Box2DPhysicsComp->EditCollisionShape(Shape);
		}
	}
}

void Player::OnMovementModeSwitch(EMovementMode PreviousMovementMode, EMovementMode CurrentMovementMode)
{
	if (CurrentMovementMode == EMovementMode::GROUND || CurrentMovementMode == EMovementMode::GRAPPLING_BALANCE ||
		CurrentMovementMode == EMovementMode::GRAPPLING_THROWN)
	{
		if (std::shared_ptr<JumpingMovementMode> JumpingMoveMode = std::dynamic_pointer_cast<JumpingMovementMode>(MovementComp->GetMovementModeObj(EMovementMode::JUMPING)))
			JumpingMoveMode->ResetJumpCount();
	}
}
