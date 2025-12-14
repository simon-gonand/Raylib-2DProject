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
#include "../../MovementModes/GroudMovementMode/GroundMovementMode.h"

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
	AddComponent(MovementComp);

	SetActorLocation(ActorInitialPostion);
	SetActorRotation(QuaternionIdentity());
	SetActorScale({1.0f, 1.0f});

	bIsJumping = false;
	MovementComp->SwitchMovementMode(EMovementMode::FALLING);
}

void Player::Move(const Vector2& Scale)
{
	float Magnitude = Vector2Length(Scale);
	MovementComp->SetMovementInput(Scale);
}

void Player::Slide(const float& Scale, const InputTrigger& Trigger)
{
	// Transfer to Slide MovementMode
	/*if (CurrentMovementMode == EMovementMode::FALLING)
		return;*/

	MovementComp->SwitchMovementMode(Trigger == DOWN ? EMovementMode::SLIDING : EMovementMode::GROUND);
}

void Player::Jump(const float& Scale, const InputTrigger& Trigger)
{
	bWasJumpingLastFrame = bIsJumping;
	bIsJumping = Trigger == DOWN;
}

void Player::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
	//UpdateJumpVelocity(NewVelocity);
}

void Player::PostUpdate()
{
	// Is Player Falling
	Vector3 CurrentVelocity = PhysicsComp->GetLinearVelocity();
	if (FloatEquals(CurrentVelocity.y, 0.0f)) {
			MovementComp->SwitchMovementMode(EMovementMode::GROUND);
	}
	else {
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

void Player::UpdateJumpVelocity(Vector2& NewVelocity)
{
	if (bIsJumping && FloatEquals(NewVelocity.y, 0.0f))
	{
		NewVelocity = Vector2Add(NewVelocity, { 0.0f, JumpSpeed });
	}
	else if (bWasJumpingLastFrame)
	{
		if(!bIsJumping && NewVelocity.y < 0.0f)
			NewVelocity.y = NewVelocity.y / 1.5f;

		bWasJumpingLastFrame = false;
	}
}

std::shared_ptr<AnimationManager> Player::CreatePlayerAnimationManager()
{
	std::shared_ptr<PlayerAnimationManager> Result = std::make_shared<PlayerAnimationManager>();
	Result->Initialize(std::static_pointer_cast<Player>(shared_from_this()));
	return Result;
}
