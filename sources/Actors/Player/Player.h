#pragma once

#include "../BaseClass/Actor.h"

class Player: public Actor
{
public:
	Player();
	virtual ~Player();

	virtual void Initialize() override;

	virtual void Draw(const Vector2& ScreenSize) override;

	void Move(const Vector2& Scale);
	void Jump(const float& Scale, const enum InputTrigger& Trigger);

	virtual void Update(float DeltaTime) override;

	std::shared_ptr<class InputComponent> InputComp;
	std::shared_ptr<class PhysicsComponent> PhysicsComp;
	std::shared_ptr<class PlayerCameraComponent> CameraComp;

private:
	float TopSpeed = 10.0f;
	float Acceleration = 1.0f;
	float DecelerationScale = 3.0f;
	float JumpSpeed = -20.0f;

	Vector2 VelocityToAdd;
	Vector2 LastVelocityIncrease;

	bool bIsJumping = false;
	bool bDecreaseVelocity = false;
	float DeaccelerateAlpha = 0.0f;

	void ClampVelocity(Vector2& NewVelocity);
};

