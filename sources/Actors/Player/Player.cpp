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
	InputComp->BindAxis<Player, &Player::Move>("Move", this);

	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(0.8f, 1.6f);
	Vector3 ActorInitialPostion = { 0.0f, -100.0f, 0.0f};

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, &PhysicsShape, 1.0f, 0.3f, 3.0f, true);
	AddComponent(PhysicsComp);

	CameraComp = std::make_shared<PlayerCameraComponent>(PlayerSPtr, Vector2({ ActorInitialPostion.x, ActorInitialPostion.y }), Vector2({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }), 0.0f, 2.5f);
	AddComponent(CameraComp);

	// Create Animation Manager + add Idle animation
	std::shared_ptr<AnimationManager> AnimManager = CreatePlayerAnimationManager();
	RendererComp = std::make_shared<SpriteSheet2DRendererComponent>(PlayerSPtr, "", Vector3({ 2.5f, -15.0f }), QuaternionIdentity(), Vector3({1.0f, 1.0f}), Vector2({3.0f, 3.0f}), AnimManager);
	AddComponent(RendererComp);

	MovementComp = std::make_shared<MovementComponent>(PlayerSPtr, PhysicsComp);
	MovementComp->AddNewMovementMode(EMovementMode::GROUND, std::make_shared<GroundMovementMode>(1.0f, 3.0f, 10.0f));
	MovementComp->AddNewMovementMode(EMovementMode::JUMPING, std::make_shared<JumpingMovementMode>(1.0f, 3.0f, 10.0f, -20.0f, MovementComp));
	MovementComp->AddNewMovementMode(EMovementMode::FALLING, std::make_shared<FallingMovementMode>(1.0f, 3.0f, 10.0f, 30.0f, 1.5f));
	MovementComp->AddNewMovementMode(EMovementMode::SLIDING, std::make_shared<SlidingMovementMode>(1.0f, 0.75f, 10.0f, MovementComp));
	AddComponent(MovementComp);

	SetActorLocation(ActorInitialPostion);
	SetActorRotation(QuaternionIdentity());
	SetActorScale({1.0f, 1.0f});

	MovementComp->SwitchMovementMode(EMovementMode::FALLING);
	MovementComp->DeactivateMovementMode(EMovementMode::SLIDING);
}

void Player::Move(const Vector2& Scale)
{
	float Magnitude = Vector2Length(Scale);
	MovementComp->SetMovementInput(Scale);
}

void Player::Slide(const float& Scale, const InputTrigger& Trigger)
{
	if (Trigger == DOWN)
	{
		MovementComp->SwitchMovementMode(EMovementMode::SLIDING);
	}
	else {
		MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}

}

void Player::Jump(const float& Scale, const InputTrigger& Trigger)
{
	if (Trigger == DOWN)
		MovementComp->SwitchMovementMode(EMovementMode::JUMPING);
	else
		MovementComp->SwitchMovementMode(EMovementMode::FALLING);
}

void Player::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	UpdateSlidingAvailability(DeltaTime);
}

void Player::PostUpdate()
{
	// Is Player Falling
	Vector3 CurrentVelocity = PhysicsComp->GetLinearVelocity();
	if (FloatEquals(CurrentVelocity.y, 0.0f)) 
	{
		if(MovementComp->GetCurrentMovementMode() != EMovementMode::SLIDING)
			MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}
	else if (MovementComp->GetCurrentMovementMode() != EMovementMode::JUMPING)
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

void Player::UpdateSlidingAvailability(float DeltaTime)
{
	Vector3 CurrentVelocity = PhysicsComp->GetLinearVelocity();
	float TopSpeed = MovementComp->GetCurrentMovementTopSpeed();
	if ((CurrentVelocity.x < -TopSpeed / 2.0f) || (CurrentVelocity.x > TopSpeed / 2.0f))
	{
		CurrentTimeBeforeActivateSliding += DeltaTime;
		if (CurrentTimeBeforeActivateSliding >= TimeBeforeActivateSliding)
			MovementComp->ActivateMovementMode(EMovementMode::SLIDING);
	}
	else
	{
		CurrentTimeBeforeActivateSliding = 0.0f;
		MovementComp->DeactivateMovementMode(EMovementMode::SLIDING);
	}
}
