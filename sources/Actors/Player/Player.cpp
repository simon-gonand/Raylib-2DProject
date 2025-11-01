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

	Vector2 ScaleSizeMeter({ 0.5f, 0.5f });
	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(ScaleSizeMeter.x, ScaleSizeMeter.y);
	Vector3 ActorInitialPostion = { 0.0f, -100.0f, 0.0f};

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, &PhysicsShape, b2Vec2(ActorInitialPostion.x, ActorInitialPostion.y), 1.0f, 0.3f, 3.0f);
	AddComponent(PhysicsComp);


	CameraComp = std::make_shared<PlayerCameraComponent>(PlayerSPtr, Vector2({ ActorInitialPostion.x, ActorInitialPostion.y }), Vector2({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }), 0.0f, 2.5f);
	AddComponent(CameraComp);

	SetActorLocation(ActorInitialPostion);
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ ScaleSizeMeter.x * 2 * PTM_RATIO, ScaleSizeMeter.y * 2 * PTM_RATIO });

	bIsJumping = false;
}

void Player::Draw(const Vector2& ScreenSize)
{

	Vector3 Scale = GetActorScale();
	Vector3 DrawLocation = GetActorLocation();

	// Draw centered to correspond to physics
	DrawRectangleGradientEx(
		{ DrawLocation.x - Scale.x / 2,
		DrawLocation.y - Scale.y / 2,
		Scale.x,
		Scale.y},
		RED, BLUE, WHITE, GREEN
	);

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
