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
	PhysicsShape.SetAsBox(25.0f, 25.0f);

	PhysicsComp = std::make_shared<Box2DPhysicsComponent>(PlayerSPtr, b2_dynamicBody, &PhysicsShape);
	AddComponent(PhysicsComp);

	SetActorLocation({ 0.0f, 200.0f });
	SetActorRotation({ 0.0f, 0.0f, 0.0f, 1.0f });
	SetActorScale({ 50.0f, 50.0f });
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