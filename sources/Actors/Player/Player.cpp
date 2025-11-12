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

Player::Player()
{
}

Player::~Player() 
{
}

void Player::Initialize()
{
	std::shared_ptr<Actor> PlayerSPtr = shared_from_this();

	VelocityToAdd = Vector2Zero();
	LastVelocityIncrease = Vector2Zero();

	InputComp = std::make_shared<InputComponent>(PlayerSPtr);
	AddComponent(InputComp);
	InputComp->BindInput<Player, &Player::Jump>("Jump", DOWN, this);
	InputComp->BindInput<Player, &Player::Jump>("Jump", RELEASED, this);
	InputComp->BindAxis<Player, &Player::Move>("Move", this);

	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(0.8f, 1.6f);
	Vector3 ActorInitialPostion = { 0.0f, -100.0f, 0.0f};

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, &PhysicsShape, 1.0f, 0.3f, 3.0f);
	AddComponent(PhysicsComp);

	CameraComp = std::make_shared<PlayerCameraComponent>(PlayerSPtr, Vector2({ ActorInitialPostion.x, ActorInitialPostion.y }), Vector2({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }), 0.0f, 2.5f);
	AddComponent(CameraComp);

	// Create Animation Manager + add Idle animation
	std::shared_ptr<AnimationManager> AnimManager = CreatePlayerAnimationManager();
	RendererComp = std::make_shared<SpriteSheet2DRendererComponent>(PlayerSPtr, "", Vector3({ 2.5f, -15.0f }), QuaternionIdentity(), Vector3({1.0f, 1.0f}), Vector2({3.0f, 3.0f}), AnimManager);
	AddComponent(RendererComp);

	SetActorLocation(ActorInitialPostion);
	SetActorRotation(QuaternionIdentity());
	SetActorScale({1.0f, 1.0f});

	bIsJumping = false;
	CurrentMovementMode = EMovementMode::FALLING;
}

void Player::Move(const Vector2& Scale)
{
	float Magnitude = Vector2Length(Scale);
	if (Magnitude > 0.0f)
	{
		DeaccelerateAlpha = 0.0f;
		
		VelocityToAdd.x = Scale.x > 0.0f ? Acceleration : -Acceleration;
		LastVelocityIncrease = PhysicsComp->GetLinearVelocity();
		bDecreaseVelocity = false;

		// Animation
	}
	else 
	{
		bDecreaseVelocity = true;
		VelocityToAdd = Vector2Zero();
	}
}

void Player::Jump(const float& Scale, const InputTrigger& Trigger)
{
	bWasJumpingLastFrame = bIsJumping;
	bIsJumping = Trigger == DOWN;
	//CurrentMovementMode = EMovementMode::FALLING;
}

void Player::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
	Vector2 NewVelocity = Vector2Add(PhysicsComp->GetLinearVelocity(), VelocityToAdd);
	UpdateJumpVelocity(NewVelocity);
	if (bDecreaseVelocity) 
	{
		DeaccelerateAlpha += DeltaTime * DecelerationScale;
		DeaccelerateAlpha = Clamp(DeaccelerateAlpha, 0.0f, 1.0f);
		NewVelocity.x = Lerp(LastVelocityIncrease.x, 0.0f, DeaccelerateAlpha);
	}
	ClampVelocity(NewVelocity);
	PhysicsComp->SetLinearVelocity(NewVelocity);
	if (FloatEquals(NewVelocity.y, 0.0f)) {
		CurrentMovementMode = EMovementMode::GROUND;
	}
	else {
		CurrentMovementMode = EMovementMode::FALLING;
	}
}

EMovementMode Player::GetCurrentMovementMode() const
{
	return CurrentMovementMode;
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

void Player::ClampVelocity(Vector2& NewVelocity)
{
	if (NewVelocity.x > 0.0f) 
	{
		NewVelocity.x = Clamp(NewVelocity.x, 0.0f, TopSpeed);
	}
	else 
	{
		NewVelocity.x = Clamp(NewVelocity.x, -TopSpeed, 0.0f);
	}
}

std::shared_ptr<AnimationManager> Player::CreatePlayerAnimationManager()
{
	std::shared_ptr<PlayerAnimationManager> Result = std::make_shared<PlayerAnimationManager>();
	Result->Initialize(std::static_pointer_cast<Player>(shared_from_this()));
	Result->AddAnimationFromTexture("Idle", "assets/Characters/Player/SpriteSheets/_Idle.png", 10, 1, 0.15f, true, 0, 9);
	Result->AddAnimationFromTexture("Jump", "assets/Characters/Player/SpriteSheets/_Jump.png", 3, 1, 0.05f, true, 0, 2);
	Result->AddAnimationFromTexture("Movement", "assets/Characters/Player/SpriteSheets/_Run.png", 10, 1, 0.05f, true, 0, 9);
	return Result;
}
