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

	InputComp = std::make_shared<InputComponent>(PlayerSPtr);
	AddComponent(InputComp);
	InputComp->BindInput<Player, &Player::Jump>("Jump", PRESSED, this);
	InputComp->BindAxis<Player, &Player::Move>("Move", this);

	b2PolygonShape PhysicsShape;
	PhysicsShape.SetAsBox(50.0f, 50.0f);

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, &PhysicsShape);
	AddComponent(PhysicsComp);

	SetActorLocation({ 0.0f, 0.0f });
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ 1.0f, 1.0f });
}

void Player::Draw(const Vector2& ScreenSize)
{
	Vector3 ScaledLocation = Vector3Multiply(GetActorLocation(), GetActorScale());
	Vector3 DrawWorldLocation = Vector3RotateByQuaternion(ScaledLocation, GetActorRotation()); // weird though
	Vector2 DrawLocation = ConvertWorldToScreen({ DrawWorldLocation.x, DrawWorldLocation.y }, ScreenSize);
	DrawRectangleGradientEx({ DrawLocation.x, DrawLocation.y, 50.0f, 50.0f }, RED, BLUE, WHITE, GREEN);
}

void Player::Move(const Vector2& Scale)
{
	float Magnitude = Vector2Length(Scale);
	if (Magnitude > 0.0f) 
	{
		AddActorLocation({Scale.x, Scale.y});
		std::cout << "Move: [" << Scale.x << ", " << Scale.y << "]" << std::endl;
	}
}

void Player::Jump(const float& Scale)
{
	std::cout << "Jump: " << Scale << std::endl;
}