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

Player::Player()
{
}

Player::~Player() 
{
}

void Player::Initialize()
{
	std::shared_ptr PlayerSPtr = shared_from_this();

	PreviousMovingVelocity = Vector2Zero();
	CurrentMovingVelocity = Vector2Zero();

	InputComp = std::make_shared<InputComponent>(PlayerSPtr);
	AddComponent(InputComp);
	InputComp->BindInput<Player, &Player::Jump>("Jump", PRESSED, this);
	InputComp->BindInput<Player, &Player::Jump>("Jump", RELEASED, this);
	InputComp->BindAxis<Player, &Player::Move>("Move", this);

	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(25.0f, 25.0f);

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, &PhysicsShape);
	AddComponent(PhysicsComp);

	SetActorLocation({ 0.0f, 200.0f });
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ 50.0f, 50.0f });

	bIsJumping = false;
}

void Player::Draw(const Vector2& ScreenSize)
{
	Vector3 Scale = GetActorScale();
	Vector2 DrawLocation = GetLocationToDraw(ScreenSize);
	DrawRectangleGradientEx({ DrawLocation.x, DrawLocation.y, Scale.x, Scale.y}, RED, BLUE, WHITE, GREEN);
}

void Player::Move(const Vector2& Scale)
{
	float Magnitude = Vector2Length(Scale);
	PreviousMovingVelocity = CurrentMovingVelocity;
	if (Magnitude > 0.0f) 
	{
		CurrentMovingVelocity = Vector2Add(CurrentMovingVelocity, Scale);
		std::cout << "Move: [" << Scale.x << ", " << Scale.y << "]" << std::endl;
	}
	else if(CurrentMovingVelocity.x != 0.0f || CurrentMovingVelocity.y != 0.0f)
	{
		float XValueToSubstract = 0.0f;
		float YValueToSubstract = 0.0f;
		if (CurrentMovingVelocity.x != 0.0f)
		{
			XValueToSubstract = CurrentMovingVelocity.x > 0.0f ? 1.0f : -1.0f;
		}
		if (CurrentMovingVelocity.y != 0.0f)
		{
			YValueToSubstract = CurrentMovingVelocity.y > 0.0f ? 1.0f : -1.0f;
		}
		CurrentMovingVelocity = Vector2Subtract(CurrentMovingVelocity, { XValueToSubstract, YValueToSubstract });
	}
}

void Player::Jump(const float& Scale, const InputTrigger& Trigger)
{
  	std::cout << "Jump: " << Scale << std::endl;
	bIsJumping = Trigger == PRESSED;
}

void Player::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);
	Vector2 VelocityWithoutInput = Vector2Subtract(PhysicsComp->GetLinearVelocity(), PreviousMovingVelocity);
	Vector2 NewVelocity = Vector2Add(VelocityWithoutInput, CurrentMovingVelocity);
	if (bIsJumping) 
	{
		NewVelocity = Vector2Add(NewVelocity, { 0.0f, 1.0f });
	}
	PhysicsComp->SetLinearVelocity(NewVelocity);

}
