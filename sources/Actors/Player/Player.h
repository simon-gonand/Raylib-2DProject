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
	void Jump(const float& Scale);

	virtual void Update(float DeltaTime) override;

	std::shared_ptr<class InputComponent> InputComp;
	std::shared_ptr<class PhysicsComponent> PhysicsComp;

private:
	Vector2 PreviousMovingVelocity;
	Vector2 CurrentMovingVelocity;
};

