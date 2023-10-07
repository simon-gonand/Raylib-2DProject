#include "Player.h"

#include <memory>
#include <iostream>
#include <functional>
#include <raylib.h>

#include "../../Components/Inputs/InputComponent.h"
#include "../BaseClass/Actor.h"
#include "../../Managers/Inputs/InputManager.h"

Player::Player()
{
	InputComp = std::make_shared<InputComponent>(std::make_shared<Player>(*this));
	AddComponent(InputComp);
	InputComp->BindInput<Player, &Player::Jump>("Jump", PRESSED, this);
	InputComp->BindAxis<Player, &Player::Move>("Move", this);
}

Player::~Player() 
{
}

void Player::Draw()
{
	DrawRectangleGradientEx({ ((float)GetScreenWidth() / 2) - 25, ((float)GetScreenHeight() / 2) - 25, 50.0f, 50.0f }, RED, BLUE, WHITE, GREEN);
}

void Player::Move(const MyVector2& Scale)
{
	float Magnitude = Scale.GetMagnitude();
	if(Magnitude > 0.0f)
		std::cout << "Move: " << Scale.ToString() << std::endl;
}

void Player::Jump(const float& Scale)
{
	std::cout << "Jump: " << Scale << std::endl;
}